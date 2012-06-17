<?php

/**
 * @file media_screencast/includes/themes/media_screencast.theme.inc
 *
 * Theme and preprocess functions for Media: Screencast.
 */

/**
 * Preprocess function for theme('media_screencast_video').
 */
function media_screencast_preprocess_media_screencast_video(&$variables) {
  // Build the URL for display.
  $uri = $variables['uri'];
  $wrapper = file_stream_wrapper_get_instance_by_uri($uri);
  $parts = $wrapper->get_parameters();
  $variables['video_id'] = check_plain($parts['t']);

  foreach (array('width', 'height', 'quality', 'bgcolor', 'wmode', 'fullscreen', 'scale', 'allowScriptAccess', 'frameborder', 'scrolling', 'blurover') as $variable_name) {
    $variables[$variable_name] = _media_screencast_default_theme_variable($variable_name);
  }

  $variables['fullscreen'] = $variables['fullscreen'] ? 'true' : 'false';
  $variables['blurover'] = $variables['blurover'] ? 'true' : 'false';

  $variables['wrapper_id'] = 'media-screencast-' . $variables['video_id'] . '-' . $variables['id'];

  $variables['users'] =  check_plain($parts['users']);
  $variables['folders'] =  check_plain($parts['folders']);
  $variables['media'] =  check_plain($parts['media']);
  $variables['filename'] =  check_plain($parts['filename']);
  $variables['url_parts'] = 'users/' . $variables['users'] . '/folders/' . $variables['folders'] . '/media/' . $variables['media'];
  $variables['url_content'] = 'http://content.screencast.com/' . $variables['url_parts'];

  $variables['output'] = <<<OUTPUT
    <object width="{$variables['width']}" height="{$variables['height']}" type="application/x-shockwave-flash" data="{$variables['url_content']}/mp4h264player.swf">
      <param name="movie" value="{$variables['url_content']}/mp4h264player.swf"></param>
      <param name="quality" value="{$variables['quality']}" />
      <param name="bgcolor" value="{$variables['bgcolor']}" />
      <param name="flashVars" value="thumb={$variables['url_content']}/FirstFrame.jpg&containerwidth={$variables['width']}&containerheight={$variables['height']}&content={$variables['url_content']}/{$variables['filename']}&blurover={$variables['blurover']}" />
      <param name="allowFullScreen" value="{$variables['fullscreen']}"></param>
      <param name="scale" value="{$variables['scale']}" />
      <param name="allowScriptAccess" value="{$variables['allowScriptAccess']}" />
      <param name="wmode" value="{$variables['wmode']}" />
      <param name="base" value="{$variables['url_content']}/" />
      <iframe type="text/html" frameborder="{$variables['frameborder']}" scrolling="{$variables['scrolling']}" style="overflow:hidden;" src="http://www.screencast.com/{$variables['url_parts']}/embed" height="{$variables['height']}" width="{$variables['width']}" ></iframe>
    </object>
OUTPUT;
}

function _media_screencast_default_theme_variable($variable_name) {
  return isset($variables[$variable_name]) ? $variables[$variable_name] : media_screencast_variable_get($variable_name);
}
