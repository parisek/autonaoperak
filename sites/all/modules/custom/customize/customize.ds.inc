<?php

function customize_car_title_render($field, $title = NULL) {
  $content = '';

  try {

    $node = $field['entity'];
    $wrapper = entity_metadata_wrapper('node', $field['entity']);

    $content .= '<h1 class="page-header">' . $wrapper->label() . '</h1>';
    if(!empty($wrapper->field_car_anotation->value())) {
      $content .= '<div class="subtitle">' . $wrapper->field_car_anotation->value() . '</div>';
    }

  }catch (EntityMetadataWrapperException $exc) {
    watchdog(
      'customize',
      'See '  . __FUNCTION__ . '() <pre>' .  $exc->getTraceAsString() . '</pre>',
       NULL, WATCHDOG_ERROR
    );
  }

  return $content;
}

function customize_car_description_render($field, $title = NULL) {
  $content = '';

  try {

    $node = $field['entity'];
    $wrapper = entity_metadata_wrapper('node', $field['entity']);

    if(!empty($wrapper->field_car_description->value()['safe_value'])) {
      $content .= '<h2>Popis vozu</h2>';
      $content .= '<div class="description">' . $wrapper->field_car_description->value()['safe_value'] . '</div>';
    }
    if(!empty($wrapper->field_car_gear->value()['safe_value'])) {
      $content .= '<h2>Příplatková výbava v ceně vozu</h2>';
      $content .= '<div class="gear">';
      $content .= $wrapper->field_car_gear->value()['safe_value'];
      $content .= '<p>Výbavu vozu je možné upravit na míru vašim požadavkům.</p>';
      $content .= '</div>';
    }
    if(!empty($wrapper->field_car_pdf->value())) {
      $file = $wrapper->field_car_pdf->value();
      $filesize = format_size($file['filesize']);
      $url = file_create_url($file['uri']);
      $content .= '<div class="file">';
      $content .= l('Podrobná specifikace vozu (PDF, ' . $filesize .')', $url);
      $content .= '</div>';
    }

  }catch (EntityMetadataWrapperException $exc) {
    watchdog(
      'customize',
      'See '  . __FUNCTION__ . '() <pre>' .  $exc->getTraceAsString() . '</pre>',
       NULL, WATCHDOG_ERROR
    );
  }

  return $content;
}

function customize_car_contact_render($field, $title = NULL) {
  $content = '';

  try {

    $node = $field['entity'];
    $wrapper = entity_metadata_wrapper('node', $field['entity']);

    $content .= '<h2>Ozvěte se nám a jezděte už brzy v novém voze Škoda OCTAVIA</h2>';
    $content .= '<div class="phone">';
    $content .= '601 601 806<br>601 601 805';
    $content .= '</div>';
    $content .= '<div class="morelink">';
    $content .= '<a href="#contact" class="btn btn-primary btn-lg">Mám zájem o tento vůz</a>';
    $content .= '</div>';

  }catch (EntityMetadataWrapperException $exc) {
    watchdog(
      'customize',
      'See '  . __FUNCTION__ . '() <pre>' .  $exc->getTraceAsString() . '</pre>',
       NULL, WATCHDOG_ERROR
    );
  }

  return $content;
}

function customize_car_pricelist_render($field, $title = NULL) {
  $content = '';

  try {

    $node = $field['entity'];
    $wrapper = entity_metadata_wrapper('node', $field['entity']);

    $pricelist = [];
    foreach ($wrapper->field_car_pricelist->getIterator() as $delta => $item_wrapper) {
      if(!empty($item_wrapper->field_pricelist_km->value()) &&
         !empty($item_wrapper->field_pricelist_year->value()) &&
         !empty($item_wrapper->field_pricelist_price->value())
        ) {
        $km = $item_wrapper->field_pricelist_km->value();
        $year = $item_wrapper->field_pricelist_year->value();
        $deposit = $item_wrapper->field_pricelist_deposit->value();

        if(!isset($pricelist[$km])) {
          $pricelist[$km]['name'] = $item_wrapper->field_pricelist_km->label();
          $pricelist[$km]['year'] = [];
          $pricelist[$km]['price'] = [];

        }
        if(!empty($deposit) && !isset($pricelist[$km]['deposit'])) {
          $pricelist[$km]['deposit'][$deposit]['name'] = number_format($deposit, 0, ',', ' ') . '&nbsp;Kč';
        }

        $pricelist[$km]['year'][$year] = [
          'value' => $item_wrapper->field_pricelist_year->label(),
        ];
        $pricelist[$km]['price'][$year] = [
          'value' => number_format($item_wrapper->field_pricelist_price->value(), 0, ',', ' ') . '&nbsp;Kč',
        ];

        // deposit is not required
        if(!empty($deposit)) {
          $pricelist[$km]['deposit'][$deposit]['items'][$year] = [
            'value' => number_format($item_wrapper->field_pricelist_price2->value(), 0, ',', ' ') . '&nbsp;Kč',
          ];
        }
      }
    }
    $data = [];
    $data['pricelist'] = $pricelist;

    $content .= theme('customize_car_pricelist', array('data' => $data));

  }catch (EntityMetadataWrapperException $exc) {
    watchdog(
      'customize',
      'See '  . __FUNCTION__ . '() <pre>' .  $exc->getTraceAsString() . '</pre>',
       NULL, WATCHDOG_ERROR
    );
  }

  return $content;
}

function customize_faq_render($field, $title = NULL) {
  $content = '';

  try {

    // Select all FAQs
    $query = new EntityFieldQuery();

    $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'faq')
      ->propertyCondition('status', NODE_PUBLISHED)
      ->propertyOrderBy('title', 'ASC');

    $result = $query->execute();

    $faq = [];
    if (isset($result['node'])) {
      $nids = array_keys($result['node']);
      $items = entity_load('node', $nids);

      foreach ($items as $item) {
        $wrapper = entity_metadata_wrapper('node', $item);
        $faq[] = [
          'id' => $wrapper->getIdentifier(),
          'title' => $wrapper->label(),
          'description' => $wrapper->body->value()['safe_value'],
        ];
      }
    }

    $content .= theme('customize_faq', array('question' => $faq, 'data' => array()));

  }catch (EntityMetadataWrapperException $exc) {
    watchdog(
      'customize',
      'See '  . __FUNCTION__ . '() <pre>' .  $exc->getTraceAsString() . '</pre>',
       NULL, WATCHDOG_ERROR
    );
  }

  return $content;
}
