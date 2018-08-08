<?php

/**
 * Implements hook_block_info().
 */
function customize_block_info() {

  $blocks['hp_slider'] = array(
    'info' => t('Customize: HP Slider')
  );
  $blocks['hp_offer'] = array(
    'info' => t('Customize: HP Offer')
  );
  $blocks['hp_brand_car'] = array(
    'info' => t('Customize: HP Brand Car')
  );
  $blocks['category_car'] = array(
    'info' => t('Customize: Category car')
  );
  $blocks['category_stock'] = array(
    'info' => t('Customize: Category stock')
  );
  $blocks['category_used'] = array(
    'info' => t('Customize: Category used')
  );
  $blocks['subcategory_car'] = array(
    'info' => t('Customize: Subcategory car')
  );
  $blocks['subcategory_stock'] = array(
    'info' => t('Customize: Subcategory stock')
  );
  $blocks['subcategory_used'] = array(
    'info' => t('Customize: Subcategory used')
  );
  $blocks['product_list_car'] = array(
    'info' => t('Customize: Product list car')
  );
  $blocks['product_list_stock'] = array(
    'info' => t('Customize: Product list stock')
  );
  $blocks['product_list_used'] = array(
    'info' => t('Customize: Product list used')
  );
  $blocks['faq'] = array(
    'info' => t('Customize: FAQ')
  );
  $blocks['howto'] = array(
    'info' => t('Customize: How to')
  );
  $blocks['sidebar_contact'] = array(
    'info' => t('Customize: Contact form - sidebar')
  );
  $blocks['vat'] = array(
    'info' => t('Customize: VAT Switch')
  );
  $blocks['responsive_switch'] = array(
    'info' => t('Customize: Responsive Switch')
  );
  $blocks['404'] = array(
    'info' => t('Customize: 404')
  );

  return $blocks;
}

/**
 * Implements hook_block_view().
 */
function customize_block_view($delta='') {
  $block = array();

  switch($delta) {
    case 'hp_slider':
      $block['content'] = customize_hp_slider_content();
      break;
    case 'hp_offer':
      $block['content'] = customize_hp_offer_content();
      break;
    case 'hp_brand_car':
      $block['content'] = customize_hp_brand_car_content();
      break;
    case 'category_car':
      $block['content'] = customize_category_car_content();
      break;
    case 'category_stock':
      $block['content'] = customize_category_stock_content();
      break;
    case 'category_used':
      $block['content'] = customize_category_used_content();
      break;
    case 'subcategory_car':
      $block['content'] = customize_subcategory_car_content();
      break;
    case 'subcategory_stock':
      $block['content'] = customize_subcategory_stock_content();
      break;
    case 'subcategory_used':
      $block['content'] = customize_subcategory_used_content();
      break;
    case 'product_list_car':
      $block['content'] = array(
        '#markup' => customize_product_list_car_content(),
        '#attached' => array(
          'js' => array(
            array(
              'data' => drupal_get_path('module', 'customize') . '/js/product-list.js',
            ),
          )
        ),
      );
      break;
    case 'product_list_stock':
      $block['content'] = array(
        '#markup' => customize_product_list_stock_content(),
        '#attached' => array(
          'js' => array(
            array(
              'data' => drupal_get_path('module', 'customize') . '/js/product-list.js',
            ),
          )
        ),
      );
      break;
    case 'product_list_used':
      $block['content'] = array(
        '#markup' => customize_product_list_used_content(),
        '#attached' => array(
          'js' => array(
            array(
              'data' => drupal_get_path('module', 'customize') . '/js/product-list.js',
            ),
          )
        ),
      );
      break;
    case 'sidebar_contact':
      $block['content'] = customize_sidebar_contact_content();
      break;
    case 'faq':
      $block['content'] = customize_faq_content();
      break;
    case 'howto':
      $block['content'] = customize_howto_content();
      break;
    case 'vat':
      $block['content'] = customize_vat_content();
      break;
    case 'responsive_switch':
      $block['content'] = customize_responsive_switch_content();
      break;
    case '404':
      $block['content'] = customize_404_content();
      break;
  }

  return $block;
}

/**
 * Callback for block Customize: HP Slider.
 */
function customize_hp_slider_content() {

  global $language;

  $content = '';

  try {

    $slides = [];

    $query = new EntityFieldQuery();

    $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'slider')
      ->propertyCondition('status', NODE_PUBLISHED)
      ->propertyCondition('language', $language->language)
      ->fieldOrderBy('field_weight', 'value', 'ASC')
      ->propertyOrderBy('created', 'DESC');

    $result = $query->execute();

    if (isset($result['node'])) {
      $nids = array_keys($result['node']);
      $items = entity_load('node', $nids);

      foreach ($items as $item) {
        $wrapper = entity_metadata_wrapper('node', $item);
        $nid =  $wrapper->getIdentifier();
        $title =  $wrapper->label();
        $body = '';
        if($wrapper->body->value()) {
          $body = $wrapper->body->value()['safe_value'];
        }
        $image = '';
        if($wrapper->field_slider_image->value()) {
          $image = file_create_url($wrapper->field_slider_image->value()['uri']);
        }
        $anotation = '';
        if($wrapper->field_slider_anotation->value()) {
          $anotation = $wrapper->field_slider_anotation->value();
        }
        $link = '';
        if($wrapper->field_slider_link->value()) {
          $link = url($wrapper->field_slider_link->value()['url']);
        }
        $slides[] = array(
          'nid' => $nid,
          'title' => $title,
          'anotation' => $anotation,
          'link' => $link,
          'body' => $body,
          'image' => $image,
        );
      }
    }

    $data = [];
    $data['highlight'] = theme('customize_highlight', array('data' => array()));

    $content .= theme('customize_hp_slider', array('slides' => $slides, 'data' => $data));

  }catch (EntityMetadataWrapperException $exc) {
    watchdog(
      'customize',
      'See '  . __FUNCTION__ . '() <pre>' .  $exc->getTraceAsString() . '</pre>',
       NULL, WATCHDOG_ERROR
    );
  }

  return $content;
}

/**
 * Callback for block Customize: HP Offer.
 */
function customize_hp_offer_content() {

  global $language;

  $content = '';

  try {

    $cars = [];

    $query = new EntityFieldQuery();

    $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'car')
      ->propertyCondition('status', NODE_PUBLISHED)
      ->propertyCondition('promote', NODE_PROMOTED)
      ->propertyCondition('language', $language->language)
      ->fieldCondition('field_car_type', 'value', 'stock')
      ->fieldCondition('field_car_status', 'value', 'sale')
      ->propertyOrderBy('created', 'DESC')
      ->range(0, 15);

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
          $image = theme('image_style', array('style_name' => 'product-small', 'path' => $file['uri']));
          break;
        }

        $view = node_view($wrapper->value(), 'teaser');

        $cars[] = array(
          'nid' => $nid,
          'node' => drupal_render($view),
        );
      }
    }

    // assign value to title
    $query = db_select('node', 'n');
    $query->join('field_data_field_car_type', 's', 'n.nid = %alias.entity_id');
    $query->join('field_data_field_car_status', 't', 'n.nid = %alias.entity_id');
    $query
      ->fields('n', array('nid'))
      ->condition('n.type', 'car')
      ->condition('n.language', $language->language)
      ->condition('s.field_car_type_value', 'stock')
      ->condition('t.field_car_status_value', 'sale')
      ->condition('n.status', NODE_PUBLISHED);
    $result = $query->execute();
    $carCount = $result->rowCount();

    $data = [];
    $data['count'] = $carCount;
    $data['morelink'] = customize_get_translate_link('node/4', TRUE);
    $data['highlight'] = theme('customize_highlight', array('data' => array()));

    if(count($cars)) {
      $content .= theme('customize_hp_offer', array('cars' => $cars, 'data' => $data));
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

/**
 * Callback for block Customize: Brand Car.
 */
function customize_hp_brand_car_content() {

  $content = '';

  try {

    $brand = [];

    $items = taxonomy_get_tree(4, 0, 1, TRUE);

    foreach ($items as $item) {

      $wrapper = entity_metadata_wrapper('taxonomy_term', $item);
      $tid =  $wrapper->getIdentifier();
      $title = $wrapper->label();
      $image = '';
      if($wrapper->field_term_image->value()) {
        $file = $wrapper->field_term_image->value();
        $image = theme('image_style', array('style_name' => 'logo', 'path' => $file['uri']));
      }

      $brand[] = array(
        'tid' => $tid,
        'title' => $title,
        'image' => $image,
        'url' => url('taxonomy/term/' . $tid),
      );
    }

    $data = [];
    $data['morelink'] = customize_get_translate_link('node/2', TRUE);

    $content .= theme('customize_hp_brand_car', array('brand' => $brand, 'data' => $data));

  }catch (EntityMetadataWrapperException $exc) {
    watchdog(
      'customize',
      'See '  . __FUNCTION__ . '() <pre>' .  $exc->getTraceAsString() . '</pre>',
       NULL, WATCHDOG_ERROR
    );
  }

  return $content;
}

/**
 * Callback for block Customize: Category Car.
 */
function customize_category_car_content() {

  $content = '';

  $current_term = menu_get_object('taxonomy_term', 2);

  try {

    $brand = [];

    $tree = taxonomy_get_tree(4, 0, NULL, TRUE);
    $items = customize_get_nested_tree($tree);

    foreach ($items as $item) {

      $wrapper = entity_metadata_wrapper('taxonomy_term', $item);
      $tid =  $wrapper->getIdentifier();
      $title = $wrapper->label();

      $model = [];
      $active_model = FALSE; // check if some child model is active
      if(isset($item->children)) {
        foreach ($item->children as $child) {

          $child_wrapper = entity_metadata_wrapper('taxonomy_term', $child);
          $child_tid =  $child_wrapper->getIdentifier();
          $child_title = $child_wrapper->label();

          $class = [];
          if($current_term && $current_term->tid == $child_tid) {
            $class[] = 'active';
            $active_model = TRUE;
          }

          $model[] = array(
            'tid' => $child_tid,
            'title' => $child_title,
            'url' => url('taxonomy/term/' . $child_tid),
            'class' => $class,
          );
        }
      }

      $class = [];
      $status = '';
      if($current_term && ($current_term->tid == $tid || $active_model)) {
        $class[] = 'active';
        $status = 'open';
      }

      $brand[] = array(
        'tid' => $tid,
        'title' => $title,
        'url' => url('taxonomy/term/' . $tid),
        'model' => $model,
        'class' => $class,
        'status' => $status,
      );
    }

    $data = [];
    $content .= theme('customize_category_list', array('brand' => $brand, 'data' => $data));

  }catch (EntityMetadataWrapperException $exc) {
    watchdog(
      'customize',
      'See '  . __FUNCTION__ . '() <pre>' .  $exc->getTraceAsString() . '</pre>',
       NULL, WATCHDOG_ERROR
    );
  }

  return $content;
}

/**
 * Callback for block Customize: Category Stock.
 */
function customize_category_stock_content() {

  $content = '';

  $current_term = menu_get_object('taxonomy_term', 2);

  try {

    $brand = [];

    $tree = taxonomy_get_tree(8, 0, NULL, TRUE);
    $items = customize_get_nested_tree($tree);

    foreach ($items as $item) {

      $wrapper = entity_metadata_wrapper('taxonomy_term', $item);
      $tid =  $wrapper->getIdentifier();
      $title = $wrapper->label();

      $model = [];
      $active_model = FALSE; // check if some child model is active
      if(isset($item->children)) {
        foreach ($item->children as $child) {

          $child_wrapper = entity_metadata_wrapper('taxonomy_term', $child);
          $child_tid =  $child_wrapper->getIdentifier();
          $child_title = $child_wrapper->label();

          $class = [];
          if($current_term && $current_term->tid == $child_tid) {
            $class[] = 'active';
            $active_model = TRUE;
          }

          $model[] = array(
            'tid' => $child_tid,
            'title' => $child_title,
            'url' => url('taxonomy/term/' . $child_tid),
            'class' => $class,
          );
        }
      }

      $class = [];
      $status = '';
      if($current_term && ($current_term->tid == $tid || $active_model)) {
        $class[] = 'active';
        $status = 'open';
      }

      $brand[] = array(
        'tid' => $tid,
        'title' => $title,
        'url' => url('taxonomy/term/' . $tid),
        'model' => $model,
        'class' => $class,
        'status' => $status,
      );
    }

    $data = [];
    $content .= theme('customize_category_list', array('brand' => $brand, 'data' => $data));

  }catch (EntityMetadataWrapperException $exc) {
    watchdog(
      'customize',
      'See '  . __FUNCTION__ . '() <pre>' .  $exc->getTraceAsString() . '</pre>',
       NULL, WATCHDOG_ERROR
    );
  }

  return $content;
}

/**
 * Callback for block Customize: Category Used.
 */
function customize_category_used_content() {

  $content = '';

  $current_term = menu_get_object('taxonomy_term', 2);

  try {

    $brand = [];

    $tree = taxonomy_get_tree(9, 0, NULL, TRUE);
    $items = customize_get_nested_tree($tree);

    foreach ($items as $item) {

      $wrapper = entity_metadata_wrapper('taxonomy_term', $item);
      $tid =  $wrapper->getIdentifier();
      $title = $wrapper->label();

      $model = [];
      $active_model = FALSE; // check if some child model is active
      if(isset($item->children)) {
        foreach ($item->children as $child) {

          $child_wrapper = entity_metadata_wrapper('taxonomy_term', $child);
          $child_tid =  $child_wrapper->getIdentifier();
          $child_title = $child_wrapper->label();

          $class = [];
          if($current_term && $current_term->tid == $child_tid) {
            $class[] = 'active';
            $active_model = TRUE;
          }

          $model[] = array(
            'tid' => $child_tid,
            'title' => $child_title,
            'url' => url('taxonomy/term/' . $child_tid),
            'class' => $class,
          );
        }
      }

      $class = [];
      $status = '';
      if($current_term && ($current_term->tid == $tid || $active_model)) {
        $class[] = 'active';
        $status = 'open';
      }

      $brand[] = array(
        'tid' => $tid,
        'title' => $title,
        'url' => url('taxonomy/term/' . $tid),
        'model' => $model,
        'class' => $class,
        'status' => $status,
      );
    }

    $data = [];
    $content .= theme('customize_category_list', array('brand' => $brand, 'data' => $data));

  }catch (EntityMetadataWrapperException $exc) {
    watchdog(
      'customize',
      'See '  . __FUNCTION__ . '() <pre>' .  $exc->getTraceAsString() . '</pre>',
       NULL, WATCHDOG_ERROR
    );
  }

  return $content;
}

/**
 * Callback for block Customize: Subcategory car.
 */
function customize_subcategory_car_content() {
  return _customize_subcategories('node', 4);
}

/**
 * Callback for block Customize: Subcategory stock.
 */
function customize_subcategory_stock_content() {
  return _customize_subcategories('node', 8);
}

/**
 * Callback for block Customize: Subcategory used.
 */
function customize_subcategory_used_content() {
  return _customize_subcategories('node', 9);
}

/**
 * Callback for block Customize: Product list car.
 */
function customize_product_list_car_content() {
  $content = '';
  $content .= '<div class="product-list-car">';
  $content .= _customize_product_list(4);
  $content .= '</div>';
  return $content;
}

/**
 * Callback for block Customize: Product list stock.
 */
function customize_product_list_stock_content() {
  $content = '';
  $content .= '<div class="product-list-stock">';
  $content .= _customize_product_list(8);
  $content .= '</div>';
  return $content;
}

/**
 * Callback for block Customize: Product list used.
 */
function customize_product_list_used_content() {
  $content = '';
  $content .= '<div class="product-list-used">';
  $content .= _customize_product_list(9);
  $content .= '</div>';
  return $content;
}

/**
 * Callback for block Customize: Sidebar Contact.
 */
function customize_sidebar_contact_content() {

  global $language;

  $webform_nid = 194;
  if($language->language == 'sk') {
    $webform_nid = 313;
  }

  $content = '';

  $content .= '<div class="content">';
  $content .= '<h2>' . t('Did not find what you were looking for?') . '</h2>';
  $content .= '<div class="subtitle">' . t('Write to us and we will contact you') . '</div>';
  $block = module_invoke('webform', 'block_view', 'client-block-' . $webform_nid);
  if($block) {
    $content .= render($block['content']);
  }
  $content .= '</div>';

  return $content;
}

/**
 * Callback for block Customize: FAQ.
 */
function customize_faq_content() {

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

/**
 * Callback for block Customize: How To.
 */
function customize_howto_content() {

  $content = '<div class="content">';
  $content .= '<h2>' . t('Simple, right? Start with your car selection.') . '</h2>';
  $content .= '<a href="' . customize_get_translate_link('node/2', TRUE) . '" class="btn btn-primary btn-lg">Osobní vozy</a>';
  $content .= '</div>';

  return $content;
}

/**
 * Callback for block Customize: VAT Switch.
 */
function customize_vat_content() {

  $content = '';

  $content .= '<div class="title">' . t('Show prices') . '</div>';
  $content .= '<form>';
  $content .= '<label class="radio-inline"><input type="radio" name="vat" value="0" checked="checked" class="vat-excluded">' . t('without VAT') . '</label>';
  $content .= '<label class="radio-inline"><input type="radio" name="vat" value="1" class="vat-included">' . t('with VAT') . '</label>';
  $content .= '</form>';

  return $content;

}

/**
 * Callback for block Customize: Responsive switch.
 */
function customize_responsive_switch_content() {

  $content = '';

  $content .= '<div class="version-toggle">';
  $content .= '<div class="visible-xs visible-sm version-desktop">' . l(t('Version for PC'), current_path(), array('query' => array('desktop' => 1))) . '</div>';
  // only when user manually set version to desktop
  if(isset($_SESSION['autonaoperakdesktop']) && $_SESSION['autonaoperakdesktop']) {
    $content .= '<div class="version-mobile">' . l(t('Mobile version'), current_path(), array('query' => array('desktop' => 0))) . '</div>';
  }
  $content .= '</div>';
  $content .= '<div class="proficio-copyright"> <a href="https://proficio.cz" target="_blank" title="Vytvořilo Proficio Marketing s.r.o." rel="nofollow" class="external"><svg version="1.1" id="Vrstva_1" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" x="0px" y="0px" width="94.371px" height="15px" viewBox="250.169 413.445 94.371 15" enable-background="new 250.169 413.445 94.371 15" xml:space="preserve"> <g> <path fill="#fff" d="M284.54,420.995c1.192,0,1.788-0.596,1.788-1.589c0-0.994-0.596-1.391-1.788-1.391h-1.192v2.98H284.54z
M281.063,416.227h3.676c2.185,0,3.874,0.795,3.874,3.179s-1.788,3.377-3.874,3.377h-1.391v3.377h-2.285V416.227z"></path> <path fill="#fff" d="M292.587,420.796h1.192c1.192,0,1.788-0.497,1.788-1.49c0-0.993-0.596-1.292-1.788-1.292h-1.192V420.796z
M295.666,426.16l-1.888-3.576h-1.192v3.576h-2.285v-9.934h3.576c2.086,0,3.874,0.695,3.874,3.08c0,1.49-0.695,2.384-1.788,2.88
l2.285,3.974H295.666z"></path> <path fill="#fff" d="M305.997,421.194c0-1.987-0.895-3.179-2.186-3.179c-1.391,0-2.186,1.192-2.186,3.179
s0.894,3.278,2.186,3.278C305.103,424.472,305.997,423.181,305.997,421.194 M299.242,421.194c0-3.278,1.887-5.066,4.47-5.066
c2.683,0,4.471,1.887,4.471,5.066c0,3.278-1.788,5.166-4.471,5.166C301.031,426.359,299.242,424.472,299.242,421.194"></path> <polygon fill="#fff" points="310.169,416.227 316.428,416.227 316.428,418.114 312.355,418.114 312.355,420.399
315.831,420.399 315.831,422.386 312.355,422.386 312.355,426.16 310.169,426.16   "></polygon> <rect x="318.116" y="416.227" fill="#fff" width="2.284" height="9.934"></rect> <path fill="#fff" d="M326.957,416.028c1.192,0,2.285,0.596,2.98,1.292l-1.192,1.391c-0.497-0.497-0.993-0.794-1.688-0.794
c-1.391,0-2.483,1.192-2.483,3.179c0,2.086,0.993,3.278,2.384,3.278c0.795,0,1.391-0.397,1.888-0.894l1.191,1.391
c-0.794,0.993-1.887,1.49-3.179,1.49c-2.582,0-4.669-1.788-4.669-5.066S324.374,416.028,326.957,416.028"></path> <rect x="331.527" y="416.227" fill="#fff" width="2.285" height="9.934"></rect> <path fill="#fff" d="M342.355,421.194c0-1.987-0.895-3.179-2.186-3.179c-1.391,0-2.186,1.192-2.186,3.179
s0.895,3.278,2.186,3.278C341.56,424.472,342.355,423.181,342.355,421.194 M335.6,421.194c0-3.278,1.888-5.066,4.47-5.066
c2.683,0,4.471,1.887,4.471,5.066c0,3.278-1.788,5.166-4.471,5.166C337.488,426.359,335.6,424.472,335.6,421.194"></path> <g> <rect x="250.169" y="413.445" fill="#f7c424" width="9.537" height="4.669"></rect> <rect x="260.699" y="413.445" fill="#32b66e" width="9.537" height="4.669"></rect> <polygon fill="#f05480" points="259.706,423.776 254.838,423.776 254.838,419.107 250.169,419.107 250.169,428.445
259.706,428.445"></polygon> <polygon fill="#ef8328" points="265.567,419.107 265.567,423.776 260.699,423.776 260.699,428.445 270.236,428.445
270.236,419.107     "></polygon> </g> </g> </svg></a></div>';

  return $content;

}

/**
 * Callback for block Customize: 404.
 */
function customize_404_content() {

  $content = '';

  $domain = $_SERVER['HTTP_HOST'];
  if(substr($domain, 0, 4) == 'www.') {
    $domain = substr($domain, 4);
  }

  $string = request_path();

  $content .= t('<span class="path">@path</span><p>We are sorry but the page you requested does not exist. It may have been deleted, relocated or renamed. This site is regularly updated and it is possible that currently some external links do not work.</p><h3>What can you do?</h3><ul><li>check the address for typing errors</li><li>return to <a href="@home">home page</a> and start over</li><li>try searching for the page using <a href="@google">Google search engine</a></li></ul><p>If the problem persists, <a href="@contact">contact us</a>.</p>', ['@path' => url($string, array('absolute' => TRUE)), '@home' => url('<front>'), '@google' => 'https://www.google.cz/#&q=' . $string . '+site:' . $domain, '@contact' => customize_get_translate_link('node/5', TRUE)]);

  return $content;
}
