<?php

function customize_car_title_render($field, $title = NULL) {
  $content = '';

  try {

    $node = $field['entity'];
    $wrapper = entity_metadata_wrapper('node', $field['entity']);

    $currency_symbol = '';
    $vat = 0;
    if($wrapper->language->value() == 'sk') {
      $currency_symbol = '€';
      $vat = variable_get('customize_vat_sk', 20);
    }elseif($wrapper->language->value() == 'cs') {
      $currency_symbol = 'Kč';
      $vat = variable_get('customize_vat_cs', 21);
    }

    $content .= '<h1 class="page-header">' . $wrapper->label() . '</h1>';
    if(!empty($wrapper->field_car_anotation->value())) {
      $content .= '<div class="subtitle">' . $wrapper->field_car_anotation->value() . '</div>';
    }
    if(!empty($wrapper->field_car_value->value())) {
      $content .= '<div class="list-price">';
      $content .= t('List price <span>!price</span> with VAT', ['!price' => number_format($wrapper->field_car_value->value(), 0, ',', ' ') . '&nbsp;' . $currency_symbol]);
      $content .= '</div>';
    }
    if(!empty($wrapper->field_price_from->value())) {
      $price = $wrapper->field_price_from->value();
      $price_vat = round($wrapper->field_price_from->value()*(1+$vat/100));
      $content .= '<div class="price">' . t('From') . ' <span class="value"><span class="js-car-price" data-price="' . $price . '" data-price-vat="' . $price_vat . '" data-symbol="' . $currency_symbol . '">' . number_format($price, 0, ',', ' ') . '&nbsp;' . $currency_symbol . '</span></span> / ' . t('month') . '</div>';
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

function customize_car_title_mobile_render($field, $title = NULL) {
  $content = '';

  try {

    $node = $field['entity'];
    $wrapper = entity_metadata_wrapper('node', $field['entity']);

    $currency_symbol = '';
    $vat = 0;
    if($wrapper->language->value() == 'sk') {
      $currency_symbol = '€';
      $vat = variable_get('customize_vat_sk', 20);
    }elseif($wrapper->language->value() == 'cs') {
      $currency_symbol = 'Kč';
      $vat = variable_get('customize_vat_cs', 21);
    }

    $content .= '<div class="page-header">' . $wrapper->label() . '</div>';
    if(!empty($wrapper->field_car_anotation->value())) {
      $content .= '<div class="subtitle">' . $wrapper->field_car_anotation->value() . '</div>';
    }
    if(!empty($wrapper->field_car_value->value())) {
      $content .= '<div class="list-price">';
      $content .= t('List price <span>!price</span> with VAT', ['!price' => number_format($wrapper->field_car_value->value(), 0, ',', ' ') . '&nbsp;' . $currency_symbol]);
      $content .= '</div>';
    }
    if(!empty($wrapper->field_price_from->value())) {
      $price = $wrapper->field_price_from->value();
      $price_vat = round($wrapper->field_price_from->value()*(1+$vat/100));
      $content .= '<div class="price">' . t('From') . ' <span class="value"><span class="js-car-price" data-price="' . $price . '" data-price-vat="' . $price_vat . '" data-symbol="' . $currency_symbol . '">' . number_format($price, 0, ',', ' ') . '&nbsp;' . $currency_symbol . '</span></span> / ' . t('month') . '</div>';
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

function customize_car_sold_render($field, $title = NULL) {
  $content = '';

  try {

    $node = $field['entity'];
    $wrapper = entity_metadata_wrapper('node', $field['entity']);

    if($wrapper->field_car_status->value() == 'end') {
      $type = $wrapper->field_car_type->value();
      $tid = 0;
      if($type == 'stock') {
        $tid = $wrapper->field_car_category2->raw();
      }elseif($type == 'catalog') {
        $tid = $wrapper->field_car_category->raw();
      }
      if(drupal_valid_path('taxonomy/term/' . $tid)) {
        $content .= '<div class="alert alert-warning">';
        $content .= t('This car is no longer on offer, choose <a href="@url">another one</a>.', ['@url' => url('taxonomy/term/' . $tid)]);
        $content .= '</div>';
      }
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

      if(empty($title)) {
        $title = $wrapper->label();
      }

      $images[] = array(
        'image' => theme('photoswipe_imagefield', array(
            'image' => array(
              'path' => $uri,
              'style_name' => ($delta) ? 'product-small' : 'product-full',
              'alt' => $title,
            ),
            'path' => file_create_url($uri),
            'dimensions' => $image_info['width'] . 'x' . $image_info['height'],
            'caption' => $title,
        )),
      );
    }

    $imageCount = count($images);
    if($imageCount) {
      $content .= '<div class="photoswipe-gallery">';
      // main image
      $content .= '<div class="product-image-full-container">';
      foreach ($images as $key => $image) {
        $content .= $image['image'];
        break;
      }
      if($wrapper->field_car_sticker->value() || $wrapper->field_car_stock->value() > 0) {
        $content .= '<ul class="stickers">';
        if($wrapper->field_car_sticker->value()) {
          $content .= '<li class="sticker sticker-' . $wrapper->field_car_sticker->raw() . '">' . $wrapper->field_car_sticker->label() . '</li>';
        }
        if($wrapper->field_car_stock->value() > 0) {
          $content .= '<li class="sticker sticker-stock">' . t('In stock') . '</li>';
        }
        $content .= '</ul>';
      }
      $content .= '</div>';

      // small images
      if($imageCount > 1) {
        $content .= '<div class="product-image-small-container">';
        foreach ($images as $key => $image) {
          if($key > 0 && $key < 5) {
            $content .= '<div class="item">';
            $content .= $image['image'];
            $content .= '</div>';
          }
        }
        $content .= '</div>';
      }
      if($imageCount > 5) {
        $content .= '<div id="showall" class="collapse">';
        $content .= '<div class="product-image-small-container">';
        foreach ($images as $key => $image) {
          if($key >= 5) {
            $content .= '<div class="item">';
            $content .= $image['image'];
            $content .= '</div>';
          }
        }
        $content .= '</div>';
        $content .= '</div>';
      }
      $content .= '</div>';
      if($imageCount > 5) {
        $content .= '<div class="morelink">';
        $content .= '<a data-toggle="collapse" data-target="#showall">' . t('Show all photos') . '</a>';
        $content .= '</div>';
      }
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
      $content .= '<h2>' . t('Car description') . '</h2>';
      $content .= '<div class="description">' . $wrapper->field_car_description->value()['safe_value'] . '</div>';
    }
    if(!empty($wrapper->field_car_gear->value()['safe_value'])) {
      $content .= '<h2>' . t('Additional equipment included in the price') . '</h2>';
      $content .= '<div class="gear">';
      $content .= $wrapper->field_car_gear->value()['safe_value'];
      if($wrapper->field_car_type->value() == 'catalog') {
        $content .= '<p>' . t('The equipment of the car can be tailored to your requirements.') . '</p>';
      }
      $content .= '</div>';
    }
    if(!empty($wrapper->field_car_pdf->value())) {
      $file = $wrapper->field_car_pdf->value();
      $filesize = format_size($file['filesize']);
      $url = file_create_url($file['uri']);
      $content .= '<div class="file">';
      $title = '<span class="icon-pdf"></span>';
      $title .= '<span class="text">' . t('Detailed vehicle specification') . ' <span class="size">(PDF, ' . $filesize .')</span></span>';
      $content .= l($title, $url, ['html' => TRUE, 'attributes' => ['target'=>'_blank']]);
      $content .= '</div>';
    }
    if(!empty($wrapper->field_car_pdf2->value())) {
      $file = $wrapper->field_car_pdf2->value();
      $filesize = format_size($file['filesize']);
      $url = file_create_url($file['uri']);
      $content .= '<div class="file" style="margin-bottom: 20px;">';
      $title = '<span class="icon-pdf"></span>';
      $title .= '<span class="text">' . t('Sample loan calculation with residual value') . ' <span class="size">(PDF, ' . $filesize .')</span></span>';
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

  global $language;

  $content = '';

  try {

    $node = $field['entity'];
    $wrapper = entity_metadata_wrapper('node', $field['entity']);

    $currency_symbol = '';
    $vat = 0;
    if($wrapper->language->value() == 'sk') {
      $currency_symbol = '€';
      $vat = variable_get('customize_vat_sk', 20);
    }elseif($wrapper->language->value() == 'cs') {
      $currency_symbol = 'Kč';
      $vat = variable_get('customize_vat_cs', 21);
    }

    // get first image
    $image = '';
    foreach ($wrapper->field_car_gallery->getIterator() as $delta => $file_wrapper) {
      $file = $file_wrapper->value();
      $title = $file_wrapper->value()['title'];

      if(empty($title)) {
        $title = $wrapper->label();
      }

      if($file) {
        $image = theme('image_style', array('style_name' => 'product-list', 'path' => $file['uri'], 'alt' => $title));
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
          $content .= '<li class="sticker sticker-stock">' . t('In stock') . '</li>';
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
      $price = $wrapper->field_price_from->value();
      $price_vat = round($wrapper->field_price_from->value()*(1+$vat/100));
      $content .= '<div class="price">' . t('From') . ' <span class="value"><span class="js-car-price" data-price="' . $price . '" data-price-vat="' . $price_vat . '" data-symbol="' . $currency_symbol . '">' . number_format($price, 0, ',', ' ') . '&nbsp;' . $currency_symbol . '</span></span> / ' . t('month') . '</div>';
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

  global $language;

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

    $content .= '<h2>' . t('Write to us and drive soon in a new car @title', ['@title' => implode($title, ' ')]) . '</h2>';
    $content .= '<div class="phone">';
    $content .= '<span class="icon-phone-huge"></span>';
    $content .= '<span class="text">';
    if($language->language == 'cs') {
      $content .= '<a href="tel:+420601601805">601 601 805</a><br>';
      $content .= '<a href="tel:+420601601807">601 601 807</a>';
    }elseif($language->language == 'sk') {
      $content .= '<a href="tel:0949350035">0949 350 035</a>';
    }
    $content .= '</span>';
    $content .= '</div>';
    $content .= '<div class="morelink">';
    $content .= '<a href="#contact" class="btn btn-primary btn-lg">' . t('I\'m interested in this car') . '</a>';
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

  global $language;

  $content = '';

  try {

    $node = $field['entity'];
    $wrapper = entity_metadata_wrapper('node', $field['entity']);

    $currency_symbol = '';
    $vat = 0;
    if($wrapper->language->value() == 'sk') {
      $currency_symbol = '€';
      $vat = variable_get('customize_vat_sk', 20);
    }elseif($wrapper->language->value() == 'cs') {
      $currency_symbol = 'Kč';
      $vat = variable_get('customize_vat_cs', 21);
    }

    $pricelist = [];
    $pricelist_mobile = [];
    foreach ($wrapper->field_car_pricelist->getIterator() as $delta => $item_wrapper) {
      if(!empty($item_wrapper->field_pricelist_km->value()) &&
         !empty($item_wrapper->field_pricelist_year->value()) &&
         !empty($item_wrapper->field_pricelist_price->value())
        ) {
        $km = $item_wrapper->field_pricelist_km->value();
        $km_label = number_format($item_wrapper->field_pricelist_km->value(), 0, ',', ' ') . '&nbsp;km';
        $year = $item_wrapper->field_pricelist_year->value();
        $year_label = $item_wrapper->field_pricelist_year->label();

        $deposit_type = 'fixed';
        if($wrapper->__isset('field_car_deposit2') && !empty($wrapper->field_car_deposit2->value())) {
          $deposit = $wrapper->field_car_deposit2->value();
        }elseif($wrapper->__isset('field_car_deposit') && !empty($wrapper->field_car_deposit->value())) {
          $deposit = $wrapper->field_car_deposit->value();
          $deposit_type = 'percentage';
        }else{
          $deposit = $item_wrapper->field_pricelist_deposit->value();
        }

        $deposit_price = 0;
        $deposit_price_vat = 0;
        $deposit_percentage = 0;
        if($deposit > 0) {
          if ($deposit_type === 'fixed') {
            $deposit_price = $deposit;
            $deposit_price_vat = round($deposit * (1 + $vat / 100));
          } elseif ($deposit_type === 'percentage') {
            $deposit_percentage = $deposit;
          }
        }
        $price = $item_wrapper->field_pricelist_price->value();
        $price_vat = round($item_wrapper->field_pricelist_price->value()*(1+$vat/100));
        $price2 = $item_wrapper->field_pricelist_price2->value();
        $price2_vat = round($item_wrapper->field_pricelist_price2->value()*(1+$vat/100));

        $pricelist_mobile[$km][] = [
          'km' => $km,
          'km_label' => $km_label,
          'year' => $year_label,
          'deposit_price' => $deposit_price,
          'deposit_price_vat' => $deposit_price_vat,
          'deposit_percentage' => $deposit_percentage,
          'deposit_type' => $deposit_type,
          'price' => $price,
          'price_vat' => $price_vat,
          'price2' => $price2,
          'price2_vat' => $price2_vat,
          'currency_symbol' => $currency_symbol,
          'vat' => $vat,
        ];

        if(!isset($pricelist[$km])) {
          $pricelist[$km]['name'] = $km_label;
          $pricelist[$km]['year'] = [];
          $pricelist[$km]['price'] = [];

        }
        if(!empty($deposit) && !isset($pricelist[$km]['deposit'])) {
          $pricelist[$km]['deposit'][$deposit] = [
            'name' => [
              'price' => $deposit_price,
              'price_vat' => $deposit_price_vat,
              'currency_symbol' => $currency_symbol,
              'vat' => $vat,
              'percentage' => $deposit_percentage,
              'type' => $deposit_type,
            ],
          ];
        }

        $pricelist[$km]['year'][$year] = [
          'value' => $year_label,
        ];
        $pricelist[$km]['price'][$year] = [
          'value' => [
            'price' => $price,
            'price_vat' => $price_vat,
            'currency_symbol' => $currency_symbol,
            'vat' => $vat,
          ],
        ];

        // deposit is not required (with service price)
        if(!empty($deposit)) {
          $pricelist[$km]['deposit'][$deposit]['items'][$year] = [
            'value' => [
              'price' => $price2,
              'price_vat' => $price2_vat,
              'currency_symbol' => $currency_symbol,
              'vat' => $vat,
            ],
          ];
        }
      }
    }

    $data = [];
    $data['pricelist'] = $pricelist;
    $data['pricelist_vat'] = $vat;
    $data['pricelist_type'] = $wrapper->field_car_pricelist_type->value();
    $data['pricelist_mobile'] = $pricelist_mobile;
    $data['car_value'] = '';
    if(!empty($wrapper->field_car_value->value())) {
      $data['car_value'] = number_format($wrapper->field_car_value->value(), 0, ',', ' ') . '&nbsp;' . $currency_symbol;
    }
    $data['car_type'] = $wrapper->field_car_type->value();
    $data['service_included'] = $wrapper->field_car_included->value()['safe_value'];
    $data['service_excluded'] = $wrapper->field_car_excluded->value()['safe_value'];

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

function customize_car_related_render($field, $title = NULL) {

  global $language;

  $content = '';

  try {

    $node = $field['entity'];
    $wrapper = entity_metadata_wrapper('node', $field['entity']);

    $data = [];
    $type = $wrapper->field_car_type->value();
    $brand_tid = $wrapper->field_car_brand->raw();
    $car_type = '';
    if($type == 'catalog') {
      $car_type = 'stock';
      $data['title'] = t('Cars immediately available');
    }elseif($type == 'stock') {
      $car_type = 'catalog';
      $data['title'] = t('Other configurations');
    }

    $cars = [];

    $query = new EntityFieldQuery();

    $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'car')
      ->propertyCondition('status', NODE_PUBLISHED)
      ->propertyCondition('language', $language->language)
      ->fieldCondition('field_car_brand', 'tid', $brand_tid)
      ->fieldCondition('field_car_status', 'value', 'sale')
      ->fieldCondition('field_car_type', 'value', $car_type)
      ->fieldOrderBy('field_weight', 'value', 'ASC');

    $result = $query->execute();

    if (isset($result['node'])) {
      $nids = array_keys($result['node']);
      $items = entity_load('node', $nids);

      foreach ($items as $item) {
        $wrapper = entity_metadata_wrapper('node', $item);
        $nid =  $wrapper->getIdentifier();
        $title = $wrapper->label();
        $image = '';
        // get first image from gallery
        foreach ($wrapper->field_car_gallery->getIterator() as $delta => $image_wrapper) {
          $file = $image_wrapper->value();
          $image = theme('image_style', array('style_name' => 'product-small', 'path' => $file['uri'], 'alt' => $title));
          break;
        }

        $view = node_view($wrapper->value(), 'teaser');

        $cars[] = array(
          'nid' => $nid,
          'node' => drupal_render($view),
        );
      }

      $data['count'] = count($items);
      $content .= theme('customize_car_related', array('cars' => $cars, 'data' => $data));
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

function customize_car_form_render($field, $title = NULL) {

  $content = '';

  try {

    $node = $field['entity'];
    $wrapper = entity_metadata_wrapper('node', $field['entity']);

    $webform_nid = 15;
    if($wrapper->language->value() == 'sk') {
      $webform_nid = 314;
    }

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
    $content .= '<h2><a name="contact" id="contact"></a>' . t('Write to us and drive soon in a new car @title', ['@title' => implode($title, ' ')]) . '</h2>';
    $content .= '<div class="subtitle">' . t('We will contact you with the offer no later than the next business day') . '</div>';
    $block = module_invoke('webform', 'block_view', 'client-block-' . $webform_nid);
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

  global $language;

  $content = '';

  try {

    // Select all FAQs
    $query = new EntityFieldQuery();

    $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'faq')
      ->propertyCondition('status', NODE_PUBLISHED)
      ->propertyCondition('language', $language->language)
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

    $content .= '<h2>' . t('Frequently Asked Questions') . '</h2>';
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

function customize_term_subcategory_used_render($field, $title = NULL) {
  $content = '';

  try {

    $term = $field['entity'];
    $content .= _customize_subcategories('taxonomy_term', 9, $term);

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
