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

function customize_car_gallery_render($field, $title = NULL) {

  $content = '';

  photoswipe_load_assets();

  try {

    $node = $field['entity'];
    $wrapper = entity_metadata_wrapper('node', $field['entity']);

    $images = [];
    foreach ($wrapper->field_car_gallery->getIterator() as $delta => $image_wrapper) {
      $uri = $image_wrapper->value()['uri'];
      $title = $image_wrapper->value()['title'];
      $image_info = image_get_info($uri);

      $images[] = array(
        'image' => theme('photoswipe_imagefield', array(
            'image' => array(
              'path' => $uri,
              'style_name' => ($delta) ? 'product-small' : 'product-full',
            ),
            'path' => file_create_url($uri),
            'dimensions' => $image_info['width'] . 'x' . $image_info['height'],
            'caption' => $title . ' - ' . $wrapper->label(),
        )),
      );
    }

    if(count($images)) {
      $content .= '<div class="photoswipe-gallery">';
      // main image
      foreach ($images as $key => $image) {
        $content .= '<div class="product-image-full-container">';
        $content .= $image['image'];
        $content .= '<span class="glyphicon glyphicon-search" aria-hidden="true"></span>';
        $content .= '</div>';
        break;
      }
      // small images
      if(count($images) > 1) {
        $content .= '<div class="product-image-small-container">';
        foreach ($images as $key => $image) {
          if($key > 0) {
            $content .= '<div class="item">';
            $content .= $image['image'];
            $content .= '</div>';
          }
        }
        $content .= '</div>';
      }
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
      $title = '<span class="icon-pdf"></span>';
      $title .= '<span class="text">Podrobná specifikace vozu <span class="size">(PDF, ' . $filesize .')</span></span>';
      $content .= l($title, $url, ['html' => TRUE, 'attributes' => ['target'=>'_blank']]);
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

function customize_car_teaser_render($field, $title = NULL) {
  $content = '';

  try {

    $node = $field['entity'];
    $wrapper = entity_metadata_wrapper('node', $field['entity']);

    // get first image
    $image = '';
    foreach ($wrapper->field_car_gallery->getIterator() as $delta => $file_wrapper) {
      $file = $file_wrapper->value();
      if($file) {
        $image = theme('image_style', array('style_name' => 'product-list', 'path' => $file['uri']));
      }
      break;
    }

    $content .= '<a href="' . url('node/' . $wrapper->getIdentifier()) . '">';

    if(!empty($image)) {
      $content .= '<div class="image">';
      $content .= $image;
      if($wrapper->field_car_sticker->value() || $wrapper->field_car_stock->value() > 0) {
        $content .= '<ul class="stickers">';
        if($wrapper->field_car_sticker->value()) {
          $content .= '<li class="sticker sticker-' . $wrapper->field_car_sticker->raw() . '">' . $wrapper->field_car_sticker->label() . '</li>';
        }
        if($wrapper->field_car_stock->value() > 0) {
          $content .= '<li class="sticker sticker-stock">Skladem</li>';
        }
        $content .= '</ul>';
      }
      $content .= '</div>';
    }

    $content .= '<h2>' . $wrapper->label() . '</h2>';
    if(!empty($wrapper->field_car_anotation->value())) {
      $content .= '<div class="subtitle">' . $wrapper->field_car_anotation->value() . '</div>';
    }

    if(!empty($wrapper->field_price_from->value())) {
      $content .= '<div class="price">Od ' . number_format($wrapper->field_price_from->value(), 0, ',', ' ') . ' Kč / měsíc</div>';
    }

    $content .= '</a>';

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

    $title = [];
    if($wrapper->field_car_brand->value()) {
      $model = $wrapper->field_car_brand;
      $parents = taxonomy_get_parents($model->getIdentifier());
      if(count($parents)) {
        foreach ($parents as $brand) {
          $title[] = $brand->name;
          break;
        }
        $title[] = $model->label();
      }
    }

    $content .= '<h2>Ozvěte se nám a jezděte už brzy v novém voze ' . implode($title, ' ') . '</h2>';
    $content .= '<div class="phone">';
    $content .= '<span class="icon-phone-huge"></span>';
    $content .= '<span class="text">';
    $content .= '<a href="tel:+420601601806">601 601 806</a><br>';
    $content .= '<a href="tel:+420601601805">601 601 805</a>';
    $content .= '</span>';
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

function customize_car_form_render($field, $title = NULL) {
  $content = '';

  try {

    $node = $field['entity'];
    $wrapper = entity_metadata_wrapper('node', $field['entity']);

    $title = [];
    if($wrapper->field_car_brand->value()) {
      $model = $wrapper->field_car_brand;
      $parents = taxonomy_get_parents($model->getIdentifier());
      if(count($parents)) {
        foreach ($parents as $brand) {
          $title[] = $brand->name;
          break;
        }
        $title[] = $model->label();
      }
    }

    $content .= '<div class="container">';
    $content .= '<div class="content">';
    $content .= '<h2><a name="contact" id="contact"></a>Napište nám a jezděte už brzy v novém voze ' . implode($title, ' ') . '</h2>';
    $content .= '<div class="subtitle">Ozveme se vám s nabídkou nejpozději následující pracovní den</div>';
    $block = module_invoke('webform', 'block_view', 'client-block-15');
    if($block) {
      $content .= render($block['content']);
    }
    $content .= '</div>';
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

    $content .= '<h2>Nejčastější dotazy</h2>';
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

function customize_term_subcategory_car_render($field, $title = NULL) {
  $content = '';

  try {

    $term = $field['entity'];
    $content .= _customize_subcategories('taxonomy_term', 4, $term);

  }catch (EntityMetadataWrapperException $exc) {
    watchdog(
      'customize',
      'See '  . __FUNCTION__ . '() <pre>' .  $exc->getTraceAsString() . '</pre>',
       NULL, WATCHDOG_ERROR
    );
  }

  return $content;
}

function customize_term_subcategory_van_render($field, $title = NULL) {
  $content = '';

  try {

    $term = $field['entity'];
    $content .= _customize_subcategories('taxonomy_term', 5, $term);

  }catch (EntityMetadataWrapperException $exc) {
    watchdog(
      'customize',
      'See '  . __FUNCTION__ . '() <pre>' .  $exc->getTraceAsString() . '</pre>',
       NULL, WATCHDOG_ERROR
    );
  }

  return $content;
}

function customize_term_subcategory_stock_render($field, $title = NULL) {
  $content = '';

  try {

    $term = $field['entity'];
    $content .= _customize_subcategories('taxonomy_term', 8, $term);

  }catch (EntityMetadataWrapperException $exc) {
    watchdog(
      'customize',
      'See '  . __FUNCTION__ . '() <pre>' .  $exc->getTraceAsString() . '</pre>',
       NULL, WATCHDOG_ERROR
    );
  }

  return $content;
}

function customize_paragraph_bullets_render($field, $title = NULL) {

  $content = '';

  try {

    $node = $field['entity'];
    $wrapper = entity_metadata_wrapper('paragraphs_item', $field['entity']);

    foreach ($wrapper->field_paragraph_bullet->value() as $delta => $bullet) {
      $content .= '<div class="item">';
      $content .= '<div class="image">';
      $content .= '<span class="number">' . ($delta+1) . '.</span>';
      $content .= '</div>';
      $content .= '<div class="description">';
      $content .= $bullet['safe_value'];
      $content .= '</div>';
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
