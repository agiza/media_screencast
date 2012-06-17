<?php

/**
 * Implementation of MediaInternetBaseHandler.
 *
 * @see hook_media_internet_providers().
 */
class MediaInternetScreencastHandler extends MediaInternetBaseHandler {
  public function parse($embedCode) {
    $pattern = '@screencast\.com/([^\?"]+)@i';
    preg_match($pattern, $embedCode, $matches);
    if (isset($matches[1])) {
      return file_stream_wrapper_uri_normalize($this->scrapeHTML('http://screencast.com/' . $matches[1]));
    }
  }

  public function claim($embedCode) {
    if ($this->parse($embedCode)) {
      return TRUE;
    }
  }

  public function save() {
    $file = $this->getFileObject();
    // If a user enters a duplicate Screencast URL, the object will be saved again.
    // Set the timestamp to the current time, so that the media item shows up
    // at the top of the media library, where they would expect to see it.
    $file->timestamp = REQUEST_TIME;
    file_save($file);
    return $file;
  }

  public function getFileObject() {
    $uri = $this->parse($this->embedCode);
    return file_uri_to_object($uri, TRUE);
  }

  public function scrapeHTML($filename) {
    // Load up the document to scrape.
    $doc = new DOMDocument();

    // Screencast tends to use sloppy HTML. Turn off error reporting.
    @$doc->loadHTMLFile($filename);

    // Get the document player object.
    $scPlayer = $doc->getElementById('scPlayer');
    if (!isset($scPlayer)) {
      return;
    }
    $data = $scPlayer->getElementsByTagName('param')->item(3)->getAttribute('value');

    // Extract the parts for the uri.
    $pattern = '@content=http://content\.screencast\.com/users/([^/]+)/folders/([^/]+)/media/([^/]+)/([^&]+)&@i';
    if (preg_match($pattern, $data, $matches)) {
      $uri = 'screencast://users/' . $matches[1] . '/folders/' . $matches[2] . '/media/' . $matches[3] . '/filename/' . $matches[4];

      // Now we need the t value.
      $domxpath = new DOMXPath($doc);
      $data = $domxpath->query("//input[@id='url']")->item(0)->getAttribute('value');

      $pattern = '@http://www.screencast.com/t/([^/]+)@i';
      if (preg_match($pattern, $data, $matches)) {
        return $uri . '/t/' . $matches[1];
      }
    }
  }
}
