<?php

/**
 * Field handler to present a link to the node.
 *
 * @ingroup views_field_handlers
 */
class custom_admin_handler_node_field_action extends views_handler_field_entity {

  function option_definition() {
    $options = parent::option_definition();

    $options['update'] = array('default' => TRUE);
    $options['replicate'] = array('default' => TRUE);
    $options['translate'] = array('default' => TRUE);
    $options['delete'] = array('default' => TRUE);

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['update'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display update field'),
      '#default_value' => $this->options['update'],
    );
    $form['replicate'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display replicate field'),
      '#default_value' => $this->options['replicate'],
    );
    $form['translate'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display translate field'),
      '#default_value' => $this->options['translate'],
    );
    $form['delete'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display delete field'),
      '#default_value' => $this->options['delete'],
    );
  }

  function render($values) {

    $content = '';

    if ($node = $this->get_value($values)) {
      if($this->options['update'] && node_access('update', $node)) {
        $content .= l('<i class="fa fa-pencil-square-o" title="' . t('Edit') . '"></i>', 'node/' . $node->nid . '/edit', array('html' => TRUE, 'attributes' => array('class' => array('btn', 'btn-edit')), 'query' => drupal_get_destination()));
      }
      if($this->options['replicate'] && drupal_valid_path('replicate/node/' . $node->nid)) {
        $content .= l('<i class="fa fa-clone" title="' . t('Replicate') . '"></i>', '/replicate/node/' . $node->nid . '', array('html' => TRUE, 'attributes' => array('class' => array('btn', 'btn-replicate')), 'query' => drupal_get_destination()));
      }
      if($this->options['translate'] && module_exists('i18n_node')) {
        $content .= l('<i class="fa fa-language" title="' . t('Translate') . '"></i>', 'node/' . $node->nid . '/translate', array('html' => TRUE, 'attributes' => array('class' => array('btn', 'btn-translate')), 'query' => drupal_get_destination()));
      }
      if($this->options['delete'] && node_access('delete', $node)) {
        $content .= l('<i class="fa fa-trash-o" title="' . t('Delete') . '"></i>', 'node/' . $node->nid . '/delete', array('html' => TRUE, 'attributes' => array('class' => array('btn', 'btn-delete')), 'query' => drupal_get_destination()));
      }
    }

    return $content;
  }
}
