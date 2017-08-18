<?php

/**
 * Implements hook_preprocess_page().
 */
function autonaoperak_preprocess_page(&$vars) {

  if ($vars['is_front']) {
    $vars['title'] = '';
    $vars['breadcrumb'] = '';
    $vars['tabs'] = '';
    // hide content from display suite
    unset($vars['page']['content']['system_main']);
  }elseif(arg(0) == 'user' && !is_numeric(arg(1))) {
    $vars['title'] = '';
    $vars['breadcrumb'] = '';
    $vars['tabs'] = '';
  }elseif(arg(0) == 'user' && arg(2) == 'edit') {
    $vars['breadcrumb'] = '';
    $vars['tabs'] = '';
  }elseif(arg(0) == 'user') {
    $vars['breadcrumb'] = '';
  }elseif(arg(0) == 'navigation404') {
    $vars['breadcrumb'] = '';
    // hide default content from 404 page
    unset($vars['page']['content']['system_main']);
  }elseif(arg(0) == 'search') {

    $vars['title'] = t('Search', array(), array('context' => 'page_title'));
    $vars['breadcrumb'] = '';
  }elseif(arg(0) == 'taxonomy' && arg(1) == 'term' && is_numeric(arg(2))) {
    $current_term = menu_get_object('taxonomy_term', 2);
    $vocabulary = $current_term->vocabulary_machine_name;
    if($vocabulary == 'category_stock') {
      // add parent name and term name to browser bar
      if(isset($current_term->depth) && $current_term->depth == 2) {
        $title = [];
        $parents = taxonomy_get_parents($current_term->tid);
        if(count($parents)) {
          foreach ($parents as $brand) {
            $title[] = $brand->name;
            break;
          }
          $title[] = $current_term->name;
          $vars['title'] = implode($title, ' ') . ' skladem na operativní leasing';
        }
      }else{
        $vars['title'] = $current_term->name . ' skladem na operativní leasing';
      }
    }elseif($vocabulary == 'category_car') {
      // add parent name and term name to browser bar
      if(isset($current_term->depth) && $current_term->depth == 2) {
        $title = [];
        $parents = taxonomy_get_parents($current_term->tid);
        if(count($parents)) {
          foreach ($parents as $brand) {
            $title[] = $brand->name;
            break;
          }
          $title[] = $current_term->name;
          $vars['title'] = implode($title, ' ') . ' na operativní leasing';
        }
      }else{
        $vars['title'] = $current_term->name . ' na operativní leasing';
      }
    }

  }

  if (!empty($vars['page']['sidebar_first'])) {
    $vars['content_column_class_custom'] = 'col-md-9 col-xs-12 main-content left-sidebar';
  }elseif (!empty($vars['page']['sidebar_second'])) {
    $vars['content_column_class_custom'] = 'col-md-7 col-xs-12 main-content right-sidebar';
  }
  else {
    $vars['content_column_class_custom'] = 'col-xs-12 main-content';
  }

  // assign value to main menu
  $query = db_select('node', 'n');
  $query->join('field_data_field_car_type', 's', 'n.nid = %alias.entity_id');
  $query->join('field_data_field_car_status', 't', 'n.nid = %alias.entity_id');
  $query
    ->fields('n', array('nid'))
    ->condition('n.type', 'car')
    ->condition('s.field_car_type_value', 'stock')
    ->condition('t.field_car_status_value', 'sale')
    ->condition('n.status', NODE_PUBLISHED);
  $result = $query->execute();
  $carCount = $result->rowCount();

  $data = [];
  $vars['cars_stock'] = $carCount;

}

/**
 * Implements hook_preprocess_html().
 */
function autonaoperak_preprocess_html(&$vars) {

  if(arg(0) == 'search') {
    $head_title = check_plain(variable_get('site_name', 'Drupal'));
    $vars['head_title'] = t('Search', array(), array('context' => 'page_title')) . ' | ' . $head_title;
  }elseif(arg(0) == 'taxonomy' && arg(1) == 'term' && is_numeric(arg(2))) {
    $current_term = menu_get_object('taxonomy_term', 2);
    $vocabulary = $current_term->vocabulary_machine_name;
    if($vocabulary == 'category_stock') {
      $head_title = check_plain(variable_get('site_name', 'Drupal'));
      // add parent name and term name to browser bar
      if(isset($current_term->depth) && $current_term->depth == 2) {
        $title = [];
        $parents = taxonomy_get_parents($current_term->tid);
        if(count($parents)) {
          foreach ($parents as $brand) {
            $title[] = $brand->name;
            break;
          }
          $title[] = $current_term->name;
          $vars['head_title'] = implode($title, ' ') . ' skladem na operativní leasing | ' . $head_title;
        }
      }else{
        $vars['head_title'] = $current_term->name . ' skladem na operativní leasing | ' . $head_title;
      }
    }elseif($vocabulary == 'category_car') {
      $head_title = check_plain(variable_get('site_name', 'Drupal'));
      // add parent name and term name to browser bar
      if(isset($current_term->depth) && $current_term->depth == 2) {
        $title = [];
        $parents = taxonomy_get_parents($current_term->tid);
        if(count($parents)) {
          foreach ($parents as $brand) {
            $title[] = $brand->name;
            break;
          }
          $title[] = $current_term->name;
          $vars['head_title'] = implode($title, ' ') . ' na operativní leasing | ' . $head_title;
        }
      }else{
        $vars['head_title'] = $current_term->name . ' na operativní leasing | ' . $head_title;
      }
    }
  }

  // complete logic is in customize_init() and customize_responsive_switch_content()
  if(isset($_SESSION['autonaoperakdesktop']) && $_SESSION['autonaoperakdesktop']) {
    $viewport = array(
      '#tag' => 'meta',
      '#attributes' => array(
        'name' => 'viewport',
        'content' => 'width=1024',
      ),
    );
  }else{
    $viewport = array(
      '#tag' => 'meta',
      '#attributes' => array(
        'name' => 'viewport',
        'content' => 'width=device-width, initial-scale=1.0',
      ),
    );
  }

  drupal_add_html_head($viewport, 'viewport');

  drupal_add_css('https://fonts.googleapis.com/css?family=Raleway:300,300i,400,400i,500,500i,700,700i&subset=latin,latin-ext', array('group' => CSS_THEME));

  $path = base_path() . path_to_theme() . '/images/touch/';

  $apple_icon = array(
    '#tag' => 'link',
    '#attributes' => array(
      'rel' => 'apple-touch-icon',
      'href' => $path . 'apple-touch-icon.png',
      'sizes' => '180x180',
    ),
  );
  drupal_add_html_head($apple_icon, 'apple_icon_180x180');

  $favicon = array(
    '#tag' => 'link',
    '#attributes' => array(
      'rel' => 'icon',
      'type' => 'image/png',
      'href' => $path . 'favicon-32x32.png',
      'sizes' => '32x32',
    ),
  );
  drupal_add_html_head($favicon, 'favicon_32x32');

  $favicon = array(
    '#tag' => 'link',
    '#attributes' => array(
      'rel' => 'icon',
      'type' => 'image/png',
      'href' => $path . 'favicon-16x16.png',
      'sizes' => '16x16',
    ),
  );
  drupal_add_html_head($favicon, 'favicon_16x16');

  $favicon = array(
    '#tag' => 'link',
    '#attributes' => array(
      'rel' => 'shortcut icon',
      'href' => $path . 'favicon.ico',
    ),
  );
  drupal_add_html_head($favicon, 'favicon');

  $manifest = array(
    '#tag' => 'link',
    '#attributes' => array(
      'rel' => 'manifest',
      'href' => $path . 'manifest.json',
    ),
  );
  drupal_add_html_head($manifest, 'manifest');

  $mask_icon = array(
    '#tag' => 'link',
    '#attributes' => array(
      'rel' => 'mask-icon',
      'href' => $path . 'safari-pinned-tab.svg',
      'color' => '#161616',
    ),
  );
  drupal_add_html_head($mask_icon, 'mask_icon');

  $browserconfig = array(
    '#tag' => 'meta',
    '#attributes' => array(
      'name' => 'msapplication-config',
      'content' => $path . 'browserconfig.xml',
    ),
  );
  drupal_add_html_head($browserconfig, 'browserconfig');

  $theme_color = array(
    '#tag' => 'meta',
    '#attributes' => array(
      'name' => 'theme-color',
      'content' => '#ffffff',
    ),
  );
  drupal_add_html_head($theme_color, 'theme_color');

  $humans = array(
    '#tag' => 'link',
    '#attributes' => array(
      'rel' => 'author',
      'type' => 'text/plain',
      'href' => base_path() . 'humans.txt',
    ),
  );
  drupal_add_html_head($humans, 'humans');

}

/**
 * Overrides theme_textarea().
 */
function autonaoperak_textarea($element) {
  $element['element']['#resizable'] = FALSE;
  return theme_textarea($element) ;
}

function autonaoperak_preprocess_region(&$variables, $hook) {
  if (in_array($variables['region'], array('content'))) {
    $variables['classes_array'][] = 'row';
  }
}

/**
 * Theme function implementation for bootstrap_search_form_wrapper.
 */
function autonaoperak_bootstrap_search_form_wrapper($variables) {
  $output = '<div class="search-form">';
  $output .= $variables['element']['#children'];
  $output .= '<button type="submit" class="btn"><span class="glyphicon glyphicon-search" aria-hidden="true" title="' . t('Search') . '"></span><span class="sr-only">' . t('Search') . '</span></button>';
  $output .= '</div>';
  return $output;
}

/**
 * Overrides theme_breadcrumb().
 */
function autonaoperak_breadcrumb($variables) {
  $breadcrumbs = $variables['breadcrumb'];
  if (!empty($breadcrumbs)) {
    // Provide a navigational heading to give context for breadcrumb links to
    // screen-reader users. Make the heading invisible with .element-invisible.
    $output = '<div class="sr-only">' . t('You are here') . '</div>';
    // Hide breadcrumb navigation if it contains only one element.
    $hide_single_breadcrumb = variable_get('path_breadcrumbs_hide_single_breadcrumb', 0);
    if ($hide_single_breadcrumb && count($breadcrumbs) == 1) {
      return FALSE;
    }

    // Bootstrap 3 compatibility. See: https://drupal.org/node/2178565
    if (is_array($breadcrumbs[count($breadcrumbs) - 1])) {
      array_pop($breadcrumbs);
    }

    // Add options for rich snippets.
    $elem_tag = 'span';
    $elem_property = '';
    $root_property = '';
    $options = array('html' => TRUE);
    $snippet = variable_get('path_breadcrumbs_rich_snippets', PATH_BREADCRUMBS_RICH_SNIPPETS_DISABLED);
    if ($snippet == PATH_BREADCRUMBS_RICH_SNIPPETS_RDFA) {

      // Add link options for RDFa support.
      $options['attributes'] = array('rel' => 'v:url', 'property' => 'v:title');
      $options['absolute'] = TRUE;

      // Set correct properties for RDFa support.
      $elem_property = ' typeof="v:Breadcrumb"';
      $root_property = ' xmlns:v="http://rdf.data-vocabulary.org/#"';
    }
    elseif ($snippet == PATH_BREADCRUMBS_RICH_SNIPPETS_MICRODATA) {

      // Add link options for microdata support.
      $options['attributes'] = array('itemprop' => 'url');
      $options['absolute'] = TRUE;

      // Set correct properties for microdata support.
      $elem_property = ' itemscope itemtype="http://data-vocabulary.org/Breadcrumb"';
      $elem_tag = 'li';

    }


    foreach ($breadcrumbs as $key => $breadcrumb) {

      // Build classes for the breadcrumbs.
      $classes = array('inline');
      $classes[] = $key % 2 ? 'even' : 'odd';
      if ($key == 0) {
        $classes[] = 'first';
      }
      if (count($breadcrumbs) == $key + 1) {
        $classes[] = 'last';
      }

      // For rich snippets support all links should be processed in the same way,
      // even if they are provided not by Path Breadcrumbs module. So I have to
      // parse html code and create links again with new properties.
      preg_match('/href="([^"]+?)"/', $breadcrumb, $matches);

      // Remove base path from href.
      $href = '';
      if (!empty($matches[1])) {
        global $base_path;
        global $language;

        $base_string = rtrim($base_path, "/");

        // Append additional params to base string if clean urls are disabled.
        if (!variable_get('clean_url', 0)) {
          $base_string .= '?q=';
        }


        // Append additional params to base string for multilingual sites.
        // @note: Only core URL detection method supported.
        $enabled_negotiation_types = variable_get("language_negotiation_language", array());
        if (!empty($enabled_negotiation_types['locale-url']) && !empty($language->prefix)) {
          $base_string .= '/' . $language->prefix;
        }


        // Means that this is href to the frontpage.
        if ($matches[1] == $base_string || $matches[1] == '' || $matches[1] == '/') {
          $href = '';
        }
        // All hrefs exept frontpage.
        elseif (stripos($matches[1], "$base_string/") === 0) {
          $href = drupal_substr($matches[1], drupal_strlen("$base_string/"));
        }
        // Other cases.
        else {
          // HREF param can't starts with '/'.
          $href = stripos($matches[1], '/') === 0 ? drupal_substr($matches[1], 1) : $matches[1];
        }


        // If HREF param is empty it should be linked to a front page.
        $href = empty($href) ? '<front>' : $href;
      }

      // Get breadcrumb title from a link like "<a href = "/path">title</a>".
      $title = trim(strip_tags($breadcrumb));

      // Wrap title in additional element for microdata support.
      if ($snippet == PATH_BREADCRUMBS_RICH_SNIPPETS_MICRODATA) {
        $title = '<span itemprop="title">' . $title . '</span>';
      }

      // Support title attribute.
      if (preg_match('/<a\s.*?title="([^"]+)"[^>]*>/i', $breadcrumb, $attr_matches)) {
        $options['attributes']['title'] = $attr_matches[1];
      }
      else {
        unset($options['attributes']['title']);
      }

      // Decode url to prevent double encoding in l().
      $href = rawurldecode($href);
      // Move query params from $href to $options.
      $href = _path_breadcrumbs_clean_url($href, $options, 'none');

      // Build new text or link breadcrumb.
      $new_breadcrumb = !empty($href) ? l($title, $href, $options) : $title;

      // Replace old breadcrumb link with a new one.
      $breadcrumbs[$key] = '<' . $elem_tag . ' class="' . implode(' ', $classes) . '"' . $elem_property . '>' . $new_breadcrumb . '</' . $elem_tag . '>';
    }

    $classes = array('breadcrumb');

    // Show contextual link if it is Path Breadcrumbs variant.
    $prefix = '';
    $path_breadcrumbs_data = path_breadcrumbs_load_variant(current_path());
    if (user_access('administer path breadcrumbs') && $path_breadcrumbs_data && isset($path_breadcrumbs_data->variant)) {
      $contextual_links = array(
        '#type' => 'contextual_links',
        '#contextual_links' => array('path_breadcrumbs' => array('admin/structure/path-breadcrumbs/edit', array($path_breadcrumbs_data->variant->machine_name))),
      );
      $prefix = drupal_render($contextual_links);
      $classes[] = 'contextual-links-region';
    }

    // Build final version of breadcrumb's HTML output.
    $output .= '<ol class="' . implode(' ', $classes) . '"' . $root_property . '>' . $prefix . implode(" ", $breadcrumbs) . '</ol>';

    return $output;


  }
  // Return false if no breadcrumbs.
  return FALSE;
}

/**
 * Overrides hook_css_alter().
 */
function autonaoperak_css_alter(&$css) {

  foreach ($css as $key => $item) {
    // remove all core CSS, selected by starts with "modules/"
    if (strpos($key, 'modules/') === 0 && !in_array($key, array('modules/contextual/contextual.css'))) {
      unset($css[$key]);
    // default views module
    }else if (strpos($key, 'sites/all/modules/views/') === 0) {
      unset($css[$key]);
    // default ds module
    }else if (strpos($key, 'sites/all/modules/ds/') === 0) {
      unset($css[$key]);
    // default ckeditor module
    }else if (strpos($key, 'sites/all/modules/ckeditor/') === 0) {
      unset($css[$key]);
    // default date module
    }else if (strpos($key, 'sites/all/modules/date/') === 0) {
      unset($css[$key]);
    }
  }
}

/**
 * Implements hook_preprocess_html_tag().
 * - Remove the type attribute from the <script>, <style> and <link> elements.
 * - Remove the CDATA comments from inline JavaScript and CSS.
 */
function autonaoperak_process_html_tag(&$vars) {
  $element = &$vars['element'];
  // Remove the "type" attribute.
  if (in_array($element['#tag'], array('script', 'link', 'style'))) {
    unset($element['#attributes']['type']);
    // Remove CDATA comments.
    if (isset($element['#value_prefix']) && ($element['#value_prefix'] == "\n<!--//--><![CDATA[//><!--\n" || $element['#value_prefix'] == "\n<!--/*--><![CDATA[/*><!--*/\n")) {
      unset($element['#value_prefix']);
    }
    if (isset($element['#value_suffix']) && ($element['#value_suffix'] == "\n//--><!]]>\n" || $element['#value_suffix'] == "\n/*]]>*/-->\n")) {
      unset($element['#value_suffix']);
    }
  }
}

/**
 * Implements hook_form_alter().
 */
function autonaoperak_form_alter(array &$form, array &$form_state = array(), $form_id = NULL) {

  if($form_id === 'search_block_form') {
    $form['search_block_form']['#attributes']['placeholder'] = t('Search for', array(), array('context' => 'Search placeholder'));
  }
}

function autonaoperak_menu_link(array $variables) {
  $variables['element']['#attributes']['class'][] = 'menu-' . $variables['element']['#original_link']['mlid'];
  return theme_menu_link($variables);
}
