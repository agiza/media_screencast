<?php

/**
 * @file media_screencast/includes/themes/media-screencast-video.tpl.php
 *
 * Template file for theme('media_screencast_video').
 *
 * Variables available:
 *  $uri - The uri to the Screencast video, such as screencast://v/xsy7x8c9.
 *  $video_id - The unique identifier of the Screencast video.
 *  $width - The width to render.
 *  $height - The height to render.
 *  $autoplay - If TRUE, then start the player automatically when displaying.
 *  $fullscreen - Whether to allow fullscreen playback.
 *
 * Note that we set the width & height of the outer wrapper manually so that
 * the JS will respect that when resizing later.
 */
?>

<div class="media-screencast-outer-wrapper" id="media-screencast-<?php print $id; ?>" style="width: <?php print $width; ?>px; height: <?php print $height; ?>px;">
  <div class="media-screencast-preview-wrapper" id="<?php print $wrapper_id; ?>">
    <?php print $output; ?>
  </div>
</div>
