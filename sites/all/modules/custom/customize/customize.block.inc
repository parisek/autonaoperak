<?php

/**
 * Implements hook_block_info().
 */
function customize_block_info() {

  $blocks['menu_dropdown'] = array(
    'info' => t('Customize: Menu with dropdown')
  );
  $blocks['hp_slider'] = array(
    'info' => t('Customize: HP Slider')
  );
  $blocks['hp_promotion'] = array(
    'info' => t('Customize: HP Promotion')
  );
  $blocks['hp_highlight'] = array(
    'info' => t('Customize: HP Highlight')
  );
  $blocks['hp_banner'] = array(
    'info' => t('Customize: HP Banner')
  );
  $blocks['hp_video'] = array(
    'info' => t('Customize: HP Video')
  );
  $blocks['product-category-list'] = array(
    'info' => t('Customize: product category list'),
  );
  $blocks['products'] = array(
    'info' => t('Customize: products'),
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
    case 'menu_dropdown':
      $block['content'] = customize_menu_dropdown_content();
      break;
    case 'hp_slider':
      $block['content'] = customize_hp_slider_content();
      break;
    case 'hp_promotion':
      $block['content'] = customize_hp_promotion_content();
      break;
    case 'hp_highlight':
      $block['content'] = customize_hp_highlight_content();
      break;
    case 'hp_banner':
      $block['content'] = customize_hp_banner_content();
      break;
    case 'hp_video':
      $block['content'] = customize_hp_video_content();
      break;
    case 'product-category-list':
      $block['content'] = customize_product_category_list_content();
      break;
    case 'products':
      $block['content'] = customize_products_content();
      break;
    case '404':
      $block['content'] = customize_404_content();
      break;
  }

  return $block;
}

/**
 * Callback for block Customize: Menu with dropdown.
 */
function customize_menu_dropdown_content() {

  $content = '';

  $tree = menu_tree_page_data('main-menu', NULL);

  $data = [];
  $menu = [];
  foreach ($tree as $item) {

    $title = $item['link']['link_title'];
    $link_path = $item['link']['link_path'];
    $active = FALSE;

    // hash from path because we need same class for different languages
    $class = ['item-' . substr(md5($link_path), 0, 3), 'menu-level-1-item'];
    // set active item
    if ($item['link']['href'] == $_GET['q'] || ($item['link']['href'] == '<front>' && drupal_is_front_page())) {
      $active = TRUE;
    }

    if($active) {
      $class[] = 'item-active';
    }

    // generate submenu
    $submenu = [];
    // for products only
    if($link_path == 'node/12') {
      $tree = menu_tree_page_data('menu-products', NULL);

      foreach ($tree as $item) {

        $title2 = $item['link']['link_title'];
        $link_path2 = $item['link']['link_path'];

        // hash from path because we need same class for different languages
        $class2 = ['item-' . substr(md5($link_path2), 0, 3), 'menu-level-2-item'];
        // set active item
        if ($item['link']['href'] == $_GET['q'] || ($item['link']['href'] == '<front>' && drupal_is_front_page())) {
          $class2[] = 'item-active';
        }

        $below = [];
        if(isset($item['below'])) {
          foreach ($item['below'] as $item_below) {

            $title3 = $item_below['link']['link_title'];
            $link_path3 = $item_below['link']['link_path'];

            // hash from path because we need same class for different languages
            $class3 = ['item-' . substr(md5($link_path3), 0, 3), 'menu-level-3-item'];
            // set active item
            if ($item_below['link']['href'] == $_GET['q'] || ($item_below['link']['href'] == '<front>' && drupal_is_front_page())) {
              $class3[] = 'item-active';
            }

            $below[] = array(
              'title' => $title3,
              'path' => $link_path3,
              'url' => url($link_path3),
              'class' => $class3,
            );
          }
        }

        $submenu[] = array(
          'title' => $title2,
          'path' => $link_path2,
          'url' => url($link_path2),
          'class' => $class2,
          'below' => $below,
        );

      }

    }

    if(count($submenu)) {
      $class[] = 'submenu';
      // add caret to allow open menu with javascript
      $title .= '<span class="submenu-toggle icon-submenu-closed"></span>';
    }

    $menu[] = array(
      'title' => $title,
      'path' => $link_path,
      'url' => url($link_path),
      'class' => $class,
      'submenu' => $submenu,
    );

  }

  $data['menu'] = $menu;

  $content .= theme('customize_menu_dropdown', array('data' => $data));

  return $content;
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
        $url = '';
        if($wrapper->field_slider_link->value()) {
          $url = url($wrapper->field_slider_link->url->value());
        }
        $slides[] = array(
          'nid' => $nid,
          'title' => $title,
          'body' => $body,
          'image' => $image,
          'url' => $url,
        );
      }
    }

    $content .= theme('customize_hp_slider', array('slides' => $slides, 'data' => array()));

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
 * Callback for block Customize: HP promotion.
 */
function customize_hp_promotion_content() {

  $content = '';

  try {

    $content .= theme('customize_hp_promotion', array('products' => array(), 'data' => array()));

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
 * Callback for block Customize: HP highlight.
 */
function customize_hp_highlight_content() {

  $content = '';

  try {

    $content .= theme('customize_hp_highlight', array('data' => array()));

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
 * Callback for block Customize: HP banner.
 */
function customize_hp_banner_content() {

  $content = '';

  try {

    $data['image'] = base_path() . path_to_theme() . '/images/banner.jpg';
    $data['title'] = 'Zimní vybavení pro celou rodinu';
    $data['description'] = 'Aenean sollicitudin, lorem quis bibendum auctor, nisi consequat ipsum, nec sagittis sem nibh id elit.';
    $data['link'] = url('<front>');

    $content .= theme('customize_hp_banner', array('data' => $data));

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
 * Callback for block Customize: HP video.
 */
function customize_hp_video_content() {

  $content = '';

  try {

    $data = [];
    $video = [];

    $query = new EntityFieldQuery();

    $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'video')
      ->propertyCondition('status', NODE_PUBLISHED)
      ->propertyCondition('promote', NODE_PROMOTED)
      ->propertyOrderBy('created', 'DESC');

    $result = $query->execute();

    if (isset($result['node'])) {
      $nids = array_keys($result['node']);
      $items = entity_load('node', $nids);

      foreach ($items as $item) {
        $wrapper = entity_metadata_wrapper('node', $item);
        $nid =  $wrapper->getIdentifier();
        $view = node_view($wrapper->value(), 'teaser');

        $video[] = array(
          'nid' => $nid,
          'node' => drupal_render($view),
        );
      }
    }

    $data['morelink'] = url('node/405');

    $content .= theme('customize_hp_video', array('video' => $video, 'data' => $data));

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
 * Callback for block Customize: article sidebar.
 */
function customize_product_category_list_content() {

  $content = '';

  $tree = menu_tree_page_data('menu-products', NULL);

  $menu = [];
  foreach ($tree as $item) {

    $title = $item['link']['link_title'];
    $link_path = $item['link']['link_path'];

    // hash from path because we need same class for different languages
    $class = ['item-' . substr(md5($link_path), 0, 3), 'menu-level-1-item'];
    // set active item
    if ($item['link']['href'] == $_GET['q'] || ($item['link']['href'] == '<front>' && drupal_is_front_page())) {
      $class[] = 'item-active';
    }

    $below = [];
    if(isset($item['below'])) {
      foreach ($item['below'] as $item_below) {

        $title2 = $item_below['link']['link_title'];
        $link_path2 = $item_below['link']['link_path'];

        // hash from path because we need same class for different languages
        $class2 = ['item-' . substr(md5($link_path2), 0, 3), 'menu-level-2-item'];
        // set active item
        if ($item_below['link']['href'] == $_GET['q'] || ($item_below['link']['href'] == '<front>' && drupal_is_front_page())) {
          $class2[] = 'item-active';
        }
        // find if current term is sibling of our term page
        $current_term = menu_get_object('taxonomy_term', 2);
        if($current_term && strpos($link_path2, 'taxonomy/term') !== FALSE) {
          $parent = taxonomy_get_parents($current_term->tid);
          if(count($parent)) {
            $parent_tids = array_keys($parent);
            $menu_tid = filter_var($link_path2, FILTER_SANITIZE_NUMBER_INT);
            if(in_array($menu_tid, $parent_tids)) {
              $class2[] = 'item-active';
            }
          }
        }

        $below[] = array(
          'title' => $title2,
          'path' => $link_path2,
          'url' => url($link_path2),
          'class' => $class2,
        );
      }
    }

    $menu[] = array(
      'title' => $title,
      'path' => $link_path,
      'url' => url($link_path),
      'class' => $class,
      'below' => $below,
    );

  }

  $data = [];
  $data['menu'] = $menu;

  $content .= theme('customize_product_menu', array('data' => $data));

  return $content;
}

function customize_products_content() {

  $content = '';

  //only if taxonomy page
  if(arg(0) == 'taxonomy' && arg(1) == 'term' && is_numeric(arg(2)) && arg(3) == '') {
    $tid = arg(2);
    $term = taxonomy_term_load($tid);
    $depth = taxonomy_term_depth_get_by_tid($term->tid); // check depth level

    $children = taxonomy_get_children($tid);
    $tree = taxonomy_get_tree(1);

    $tree = menu_tree_page_data('menu-products', NULL);
    $submenu = [];

    foreach($tree as $key => $item) {
      //check current active menu
      if ($item['link']['in_active_trail'] && $item['link']['link_path'] == current_path()) {
        foreach ($item['below'] as $item_below) {

          $image = '';
          if(strpos($item_below['link']['link_path'], 'taxonomy/term') !== FALSE) {
            $tid = filter_var($item_below['link']['link_path'], FILTER_SANITIZE_NUMBER_INT);
            $term = taxonomy_term_load($tid);
            if($term) {
              $term_wrapper = entity_metadata_wrapper('taxonomy_term', $term);
              $field_term_image = $term_wrapper->field_term_image->value();
              if($field_term_image) {
                $image = image_style_url('large', $field_term_image['uri']);
              }
            }
          }

          // set default image eg. for catalog
          if(empty($image)) {
            $image = image_style_url('large', 'public://category-default.jpg');
          }

          $submenu[] = array(
            'title' => $item_below['link']['link_title'],
            'url' => url($item_below['link']['link_path']),
            'image' => $image,
          );
        }
        break;
      }
    }

    // term description
    if(!empty($term->description)) {
      $content .= '<div class="description">' . $term->description . '</div>';
    }

    // we are in the first level so display items from menu
    if(count($submenu)) {
      $data = [];
      $data['submenu'] = $submenu;
      $content .= theme('customize_product_submenu', array('data' => $data));
    // we are in the second level so display child terms and products
    }elseif(count($children)) {
      $data = [];
      $submenu = [];
      $submenu[] = [
        'title' => 'Všechny kategorie',
        'url' => 'taxonomy/term/' . $term->tid,
      ];
      foreach ($children as $child) {
        $submenu[] = [
          'title' => $child->name,
          'url' => 'taxonomy/term/' . $child->tid,
        ];
      }
      $data['submenu'] = $submenu;

      // get all terms with products
      $tids = array_keys($children);
      // add current tid
      $tids[] = $term->tid;
      $data['products'] = views_embed_view('product_list', 'block_term', implode($tids, '+'));

      $content .= theme('customize_product_submenu2', array('data' => $data));
    // we are in the third level so display products
    }else{

      $data = [];
      $submenu = [];

      // show only if we are in level 3 eg. 1 hvězda, etc.
      if($depth == 3) {
        // get parent terms siblings
        $parent = taxonomy_get_parents($term->tid);
        $children = [];
        if($parent) {
          // get first element
          $parent = current($parent);
          $children = taxonomy_get_children($parent->tid);
        }
        if(count($children)) {
          $submenu[] = [
            'title' => 'Všechny kategorie',
            'url' => 'taxonomy/term/' . $parent->tid,
          ];
          foreach ($children as $child) {
            $submenu[] = [
              'title' => $child->name,
              'url' => 'taxonomy/term/' . $child->tid,
            ];
          }
        }
      }

      $data['submenu'] = $submenu;
      $data['products'] = views_embed_view('product_list', 'block_term', $term->tid);

      $content .= theme('customize_product_submenu2', array('data' => $data));
    }

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
  $content .= '<li>zkuste stránku vyhledat prostřednictvím vyhledávače <a href="https://www.google.cz/#&q=' . $string . '+site:stigasport.cz">Google</a></li>';
  $content .= '</ul>';
  $content .= '<p>Pokud problém trvá, <a href="' . url('node/17') . '">kontaktujte nás</a>.</p>';

  return $content;
}
