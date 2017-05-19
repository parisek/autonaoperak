<?php

/**
 * Implements hook_views_data()
 */
function custom_admin_views_data() {

  $data = array();

  // node actions
  $data['node']['custom_admin_action'] = array(
    'field' => array(
      'title' => t('Action links'),
      'help' => t('Provide icon action links.'),
      'handler' => 'custom_admin_handler_node_field_action',
    ),
  );

  // taxonomy term actions
  $data['taxonomy_term_data']['custom_admin_action'] = array(
    'field' => array(
      'title' => t('Action links'),
      'help' => t('Provide icon action links.'),
      'handler' => 'custom_admin_handler_taxonomy_term_field_action',
    ),
  );

  // user actions
  $data['users']['custom_admin_action'] = array(
    'field' => array(
      'title' => t('Action links'),
      'help' => t('Provide icon action links.'),
      'handler' => 'custom_admin_handler_user_field_action',
    ),
  );

  return $data;
 }
