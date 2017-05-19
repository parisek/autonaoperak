<?php

/**
 * Implement hook_views_default_views().
 */
function custom_admin_views_default_views() {

  $views = array();
  $files = file_scan_directory(drupal_get_path('module', 'custom_admin'). '/views', '/.*\.view$/');

  foreach ($files as $filepath => $file) {
    require $filepath;
    if (isset($view)) {
      $views[$view->name] = $view;
    }
  }

  return $views;
}
