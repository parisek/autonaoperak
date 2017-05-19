<?php

/**
 * Field handler to present a link to the node.
 *
 * @ingroup views_field_handlers
 */
class custom_admin_handler_user_field_action extends views_handler_field_entity {

  function option_definition() {
    $options = parent::option_definition();
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
  }

  function render($values) {

    $content = '';
    if ($user = $this->get_value($values)) {
      if(user_access('administer users')) {
        $content .= l('<i class="fa fa-pencil-square-o" title="' . t('Edit') . '"></i>', 'user/' . $user->uid . '/edit', array('html' => TRUE, 'attributes' => array('class' => array('btn', 'btn-edit')), 'query' => drupal_get_destination()));
        $content .= l('<i class="fa fa-trash-o" title="' . t('Delete') . '"></i>', 'user/' . $user->uid . '/cancel', array('html' => TRUE, 'attributes' => array('class' => array('btn', 'btn-delete')), 'query' => drupal_get_destination()));
      }
    }

    return $content;
  }
}
