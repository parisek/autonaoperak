<?php

/**
 * Field handler to present a link to the node.
 *
 * @ingroup views_field_handlers
 */
class custom_admin_handler_taxonomy_term_field_action extends views_handler_field_entity {

  function option_definition() {
    $options = parent::option_definition();
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
  }

  function render($values) {

    $content = '';

    if ($term = $this->get_value($values)) {
      if(drupal_valid_path('taxonomy/term/' . $term->tid . '/edit')) {
        $content .= l('<i class="fa fa-pencil-square-o" title="' . t('Edit') . '"></i>', 'taxonomy/term/' . $term->tid . '/edit', array('html' => TRUE, 'attributes' => array('class' => array('btn', 'btn-edit')), 'query' => drupal_get_destination()));
      }
      if(module_exists('i18n_taxonomy')) {
        $content .= l('<i class="fa fa-language" title="' . t('Translate') . '"></i>', 'taxonomy/term/' . $term->tid . '/translate', array('html' => TRUE, 'attributes' => array('class' => array('btn', 'btn-translate')), 'query' => drupal_get_destination()));
      }
      if(drupal_valid_path('taxonomy/term/' . $term->tid . '/delete')) {
        $content .= l('<i class="fa fa-trash-o" title="' . t('Delete') . '"></i>', 'taxonomy/term/' . $term->tid . '/delete', array('html' => TRUE, 'attributes' => array('class' => array('btn', 'btn-delete')), 'query' => drupal_get_destination()));
      }
    }

    return $content;
  }
}
