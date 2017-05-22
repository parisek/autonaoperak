<?php

/**
 * Implements hook_block_info().
 */
function customize_block_info() {

  $blocks['hp_offer'] = array(
    'info' => t('Customize: HP Offer')
  );
  $blocks['hp_brand_car'] = array(
    'info' => t('Customize: HP Brand Car')
  );
  $blocks['hp_brand_van'] = array(
    'info' => t('Customize: HP Brand Van')
  );
  $blocks['category_car'] = array(
    'info' => t('Customize: Category car')
  );
  $blocks['category_van'] = array(
    'info' => t('Customize: Category van')
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
    case 'hp_offer':
      $block['content'] = customize_hp_offer_content();
      break;
    case 'hp_brand_car':
      $block['content'] = customize_hp_brand_car_content();
      break;
    case 'hp_brand_van':
      $block['content'] = customize_hp_brand_van_content();
      break;
    case 'category_car':
      $block['content'] = customize_category_car_content();
      break;
    case 'category_van':
      $block['content'] = customize_category_van_content();
      break;
    case '404':
      $block['content'] = customize_404_content();
      break;
  }

  return $block;
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
      ->fieldCondition('field_car_stock', 'value', 0, '>')
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
          $image = theme('image_style', array('style_name' => 'thumbnail', 'path' => $file['uri']));
          break;
        }

        $cars[] = array(
          'nid' => $nid,
          'title' => $title,
          'image' => $image,
          'url' => url('node/' . $nid),
        );
      }
    }

    $data = [];
    $data['morelink'] = url('node/4');

    $content .= theme('customize_hp_offer', array('cars' => $cars, 'data' => $data));

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
        $image = theme('image_style', array('style_name' => 'thumbnail', 'path' => $file['uri']));
      }

      $brand[] = array(
        'tid' => $tid,
        'title' => $title,
        'image' => $image,
        'url' => url('taxonomy/term/' . $tid),
      );
    }

    $data = [];
    $data['morelink'] = url('node/3');

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
 * Callback for block Customize: Brand Van.
 */
function customize_hp_brand_van_content() {

  $content = '';

  try {

    $brand = [];

    $items = taxonomy_get_tree(5, 0, 1, TRUE);

    foreach ($items as $item) {

      $wrapper = entity_metadata_wrapper('taxonomy_term', $item);
      $tid =  $wrapper->getIdentifier();
      $title = $wrapper->label();
      $image = '';
      if($wrapper->field_term_image->value()) {
        $file = $wrapper->field_term_image->value();
        $image = theme('image_style', array('style_name' => 'thumbnail', 'path' => $file['uri']));
      }

      $brand[] = array(
        'tid' => $tid,
        'title' => $title,
        'image' => $image,
        'url' => url('taxonomy/term/' . $tid),
      );
    }

    $data = [];
    $data['morelink'] = url('node/3');

    $content .= theme('customize_hp_brand_van', array('brand' => $brand, 'data' => $data));

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

  try {

    $brand = [];

    $tree = taxonomy_get_tree(4, 0, NULL, TRUE);
    $items = customize_get_nested_tree($tree);

    foreach ($items as $item) {

      $wrapper = entity_metadata_wrapper('taxonomy_term', $item);
      $tid =  $wrapper->getIdentifier();
      $title = $wrapper->label();

      $model = [];
      if(isset($item->children)) {
        foreach ($item->children as $child) {

          $child_wrapper = entity_metadata_wrapper('taxonomy_term', $child);
          $child_tid =  $child_wrapper->getIdentifier();
          $child_title = $child_wrapper->label();

          $model[] = array(
            'tid' => $child_tid,
            'title' => $child_title,
            'url' => url('taxonomy/term/' . $child_tid),
          );
        }
      }

      $brand[] = array(
        'tid' => $tid,
        'title' => $title,
        'url' => url('taxonomy/term/' . $tid),
        'model' => $model,
      );
    }

    $data = [];
    $content .= theme('customize_category_car', array('brand' => $brand, 'data' => $data));

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
 * Callback for block Customize: Category Van.
 */
function customize_category_van_content() {

  $content = '';

  try {

    $brand = [];

    $tree = taxonomy_get_tree(5, 0, NULL, TRUE);
    $items = customize_get_nested_tree($tree);

    foreach ($items as $item) {

      $wrapper = entity_metadata_wrapper('taxonomy_term', $item);
      $tid =  $wrapper->getIdentifier();
      $title = $wrapper->label();

      $model = [];
      if(isset($item->children)) {
        foreach ($item->children as $child) {

          $child_wrapper = entity_metadata_wrapper('taxonomy_term', $child);
          $child_tid =  $child_wrapper->getIdentifier();
          $child_title = $child_wrapper->label();

          $model[] = array(
            'tid' => $child_tid,
            'title' => $child_title,
            'url' => url('taxonomy/term/' . $child_tid),
          );
        }
      }

      $brand[] = array(
        'tid' => $tid,
        'title' => $title,
        'url' => url('taxonomy/term/' . $tid),
        'model' => $model,
      );
    }

    $data = [];
    $content .= theme('customize_category_van', array('brand' => $brand, 'data' => $data));

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
