<?php

/**
 * @file
 * Block area handlers. Insert a block inside of an area.
 */
class customize_handler_area_search_block extends views_handler_area {

  /**
   * Render the area
   */
  function render($empty = FALSE) {

    $search_block = drupal_get_form('search_form', NULL, check_plain(arg(2)));
    return render($search_block);

  }

}
