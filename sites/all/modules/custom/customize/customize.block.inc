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
  $blocks['subcategory_car'] = array(
    'info' => t('Customize: Subcategory car')
  );
  $blocks['subcategory_stock'] = array(
    'info' => t('Customize: Subcategory stock')
  );
  $blocks['product_list_car'] = array(
    'info' => t('Customize: Product list car')
  );
  $blocks['product_list_stock'] = array(
    'info' => t('Customize: Product list stock')
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
    case 'subcategory_car':
      $block['content'] = customize_subcategory_car_content();
      break;
    case 'subcategory_stock':
      $block['content'] = customize_subcategory_stock_content();
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
    case 'sidebar_contact':
      $block['content'] = customize_sidebar_contact_content();
      break;
    case 'faq':
      $block['content'] = customize_faq_content();
      break;
    case 'howto':
      $block['content'] = customize_howto_content();
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

  $content = '';

  try {

    $slides = [];

    $query = new EntityFieldQuery();

    $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'slider')
      ->propertyCondition('status', NODE_PUBLISHED)
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
        $slides[] = array(
          'nid' => $nid,
          'title' => $title,
          'anotation' => $anotation,
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

  $content = '';

  try {

    $cars = [];

    $query = new EntityFieldQuery();

    $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'car')
      ->propertyCondition('status', NODE_PUBLISHED)
      ->fieldCondition('field_car_type', 'value', 'stock')
      ->propertyOrderBy('created', 'DESC')
      ->range(0, 10);

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

    // assign value to main menu
    $query = db_select('node', 'n');
    $query->join('field_data_field_car_type', 's', 'n.nid = %alias.entity_id');
    $query
      ->fields('n', array('nid'))
      ->condition('n.type', 'car')
      ->condition('s.field_car_type_value', 'stock')
      ->condition('n.status', NODE_PUBLISHED);
    $result = $query->execute();
    $carCount = $result->rowCount();

    $data = [];
    $data['count'] = $carCount;
    $data['morelink'] = url('node/4');
    $data['highlight'] = theme('customize_highlight', array('data' => array()));

    if($carCount) {
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
    $data['morelink'] = url('node/2');

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
 * Callback for block Customize: Product list van.
 */
function customize_product_list_stock_content() {
  $content = '';
  $content .= '<div class="product-list-stock">';
  $content .= _customize_product_list(8);
  $content .= '</div>';
  return $content;
}

/**
 * Callback for block Customize: Sidebar Contact.
 */
function customize_sidebar_contact_content() {
  $content = '';

  $content .= '<div class="content">';
  $content .= '<h2>Nenašli jste, co jste hledali?</h2>';
  $content .= '<div class="subtitle">Napište nám a my se vám ozveme</div>';
  $block = module_invoke('webform', 'block_view', 'client-block-15');
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

/**
 * Callback for block Customize: How To.
 */
function customize_howto_content() {

  $content = '<div class="content">';
  $content .= '<h2>...to je vše. Začněte s výběrem vozu.</h2>';
  $content .= '<a href="' . url('node/2') . '" class="btn btn-primary btn-lg">Osobní vozy</a>';
  $content .= '</div>';

  return $content;
}

/**
 * Callback for block Customize: 404.
 */
function customize_404_content() {

  $string = request_path();
  $site_mail = variable_get('site_mail', '');
  $content = '';

  $content .= '<div class="path">' . url($string, array('absolute' => TRUE)) . '</div>';
  $content .= 'Je nám líto, požadovaná stránka neexistuje. Zřejmě byla odstraněna, přemístěna nebo přejmenována. Na těchto stránkách průběžně dochází k drobným úpravám a je proto možné, že některé vnější odkazy na ně nyní nefungují.';
  $content .= '<h3>Co můžete udělat?</h3>';
  $content .= '<ul>';
  $content .= '<li>pokud jste zapsali adresu ručně, zkontrolujte překlepy</li>';
  $content .= '<li>přejděte na <a href="' . url('<front>') . '">úvodní stránku webu</a> a dál pokračujte odtud</li>';
  $content .= '<li>zkuste stránku vyhledat prostřednictvím vyhledávače <a href="https://www.google.cz/#&q=' . $string . '+site:autonaoperak.cz">Google</a></li>';
  $content .= '</ul>';
  $content .= '<p>Pokud problém trvá, <a href="' . url('node/5') . '">kontaktujte nás</a>.</p>';

  return $content;
}
