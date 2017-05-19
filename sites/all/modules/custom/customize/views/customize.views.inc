<?php

/**
 * Implements hook_views_data()
 */
function customize_views_data() {

  $data = array();

  $data['views']['block-search'] = array(
    'title' => t('Search block'),
    'help' => t('Insert a search block inside an area.'),
    'area' => array(
      'handler' => 'customize_handler_area_search_block',
    ),
  );
 return $data;
}
