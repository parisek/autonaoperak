<?php

/**
 * Implementation of hook_admin_settings() for configuring the module
 */
function custom_export_admin_settings_form() {

  // Description
  $form['details'] = array(
    '#type' => 'fieldset',
    '#title' => t('Settings'),
    '#collapsible' => FALSE,
  );

  $vat = variable_get('custom_export_vat', 21);
  $form['details']['custom_export_vat'] = array(
    '#type' => 'select',
    '#title' => t('VAT'),
    '#options' => array(
      15 => '15 %',
      16 => '16 %',
      17 => '17 %',
      18 => '18 %',
      19 => '19 %',
      20 => '20 %',
      21 => '21 %',
      22 => '22 %',
    ),
    '#default_value' => $vat,
  );

  $type = [
    'stock' => 'Vozy skladem',
    'catalog' => 'Katalog vozů',
  ];

  foreach ($type as $key => $name) {
    $filename = variable_get('custom_export_' . $key, $key . '.xml');
    $form['details']['custom_export_' . $key] = array(
      '#type' => 'textfield',
      '#title' => t('For @name', ['@name' => $name]),
      '#default_value' => $filename,
      '#description' => t('File will be located at <a href="@path">@path</a> (do not forget to use xml file name extension). You can view live preview <a href="@preview">here</a>', array('@path' => url('custom-export/' . $filename, array('absolute' => TRUE)), '@preview' => url('admin/config/services/custom-export/' . $key))),
      '#maxlength' => 20,
    );
  }

  return system_settings_form($form);

}
