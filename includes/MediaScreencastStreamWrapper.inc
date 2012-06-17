<?php

/**
 * @file
 * Create a Screencast Stream Wrapper class.
 */

/**
 * The Screencast Stream Wrapper class.
 */
class MediaScreencastStreamWrapper extends MediaReadOnlyStreamWrapper {
  function interpolateUrl() {
    if (($parameters = $this->get_parameters()) && isset($parameters['t'])) {
      return 'http://screencast.com/t/' . check_plain($parameters['t']);
    }
  }

  function getTarget($f) {
    return FALSE;
  }

  static function getMimeType($uri, $mapping = NULL) {
    if (preg_match('@filename/([^/]+)/t/@i', $uri, $matches)) {
      return file_get_mimetype($matches[1]);
    }
  }

  function getOriginalThumbnailPath() {
    $parts = $this->get_parameters();
    return 'http://content.screencast.com/users/'. check_plain($parts['users']) .'/folders/'. check_plain($parts['folders']) .'/media/'. check_plain($parts['media']) .'/FirstFrame.jpg';
  }

  function getLocalThumbnailPath() {
    $parts = $this->get_parameters();
    $local_path = 'public://media-screencast/users-' . check_plain($parts['users']) .'-folders-'. check_plain($parts['folders']) .'-media-'. check_plain($parts['media']) .'-FirstFrame.jpg';
    if (!file_exists($local_path)) {
      $dirname = drupal_dirname($local_path);
      file_prepare_directory($dirname, FILE_CREATE_DIRECTORY | FILE_MODIFY_PERMISSIONS);
      @copy($this->getOriginalThumbnailPath(), $local_path);
    }
    return $local_path;
  }
}
