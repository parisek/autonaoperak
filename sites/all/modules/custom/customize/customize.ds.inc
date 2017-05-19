<?php

function customize_video_image_render($field, $title = NULL) {
  $content = '';

  try {

    $node = $field['entity'];
    $wrapper = entity_metadata_wrapper('node', $field['entity']);

    $nid = $wrapper->getIdentifier();
    $url = url('node/' . $nid);
    $title =  $wrapper->label();

    $image = '';
    if($wrapper->field_video_image->value()) {
      $image = image_style_url('video-list', $wrapper->field_video_image->value()['uri']);
    }

    $content .= '<div class="item-inner" style="background-image: url(' . $image . ')">';
    $content .= '<div class="text-container">';
    $content .= '<a href="' . $url . '">';
    $content .= '<span class="glyphicon glyphicon-play" aria-hidden="true"></span>';
    $content .= '<h3>' . $title . '</h3>';
    $content .= '</a>';
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

function customize_video_youtube_render($field, $title = NULL) {
  $content = '';

  try {

    $node = $field['entity'];
    $wrapper = entity_metadata_wrapper('node', $field['entity']);

    $nid = $wrapper->getIdentifier();

    $youtube = '';
    if($wrapper->field_video_youtube->value()) {
      $youtube = $wrapper->field_video_youtube->value()['video_id'];
    }

    $content .= '<div class="embed-responsive embed-responsive-16by9">';
    $content .= '<iframe class="embed-responsive-item" src="https://www.youtube.com/embed/' . $youtube . '"></iframe>';
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

function customize_video_related_render($field, $title = NULL) {

  $content = '';

  try {

    $node = $field['entity'];
    $wrapper = entity_metadata_wrapper('node', $field['entity']);

    $video = [];
    // exclude from our db query
    $nid_exclude = [$wrapper->getIdentifier()];

    // first add related videos
    foreach ($wrapper->field_video_related as $delta => $video_wrapper) {
      // avoid loop if referenced same video
      if($video_wrapper->getIdentifier() == $wrapper->getIdentifier()) {
        continue;
      }
      $view = node_view($video_wrapper->value(), 'teaser');
      $video[] = array(
        'nid' => $video_wrapper->getIdentifier(),
        'node' => drupal_render($view),
      );
      $nid_exclude[] = $video_wrapper->getIdentifier();

    }
    // select all videos except related and parent
    $query = new EntityFieldQuery();

    $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'video')
      ->propertyCondition('status', NODE_PUBLISHED)
      ->propertyCondition('nid', $nid_exclude, 'NOT IN');

    $result = $query->execute();
    if (isset($result['node'])) {

      $nids = array_keys($result['node']);
      // random video order
      shuffle($nids);

      $items = entity_load('node', $nids);

      foreach ($items as $item) {
        // fill with videos to 3 items
        if(count($video) < 3) {
          $video_wrapper = entity_metadata_wrapper('node', $item);
          $view = node_view($video_wrapper->value(), 'teaser');
          $video[] = array(
            'nid' => $video_wrapper->getIdentifier(),
            'node' => drupal_render($view),
          );
        }
      }

    }

    if(count($video)) {
      $content .= '<h2><span>Další videa</span></h2>';
      $content .= '<div class="row item-list">';
      foreach ($video as $video_item) {
        $content .= '<div class="col-sm-4 col-xs-12 item">';
        $content .= $video_item['node'];
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

function customize_product_title_render($field, $title = NULL) {
  $content = '';

  try {

    $node = $field['entity'];
    $wrapper = entity_metadata_wrapper('node', $field['entity']);

    $title =  $wrapper->label();

    $content .= '<h1 class="page-header"><span>' . $title . '</span></h1>';

  }catch (EntityMetadataWrapperException $exc) {
    watchdog(
      'customize',
      'See '  . __FUNCTION__ . '() <pre>' .  $exc->getTraceAsString() . '</pre>',
       NULL, WATCHDOG_ERROR
    );
  }

  return $content;
}

function customize_product_price_render($field, $title = NULL) {
  $content = '';

  try {

    $node = $field['entity'];
    $wrapper = entity_metadata_wrapper('node', $field['entity']);

    $price = '';
    $price_formatted = '';
    if($wrapper->field_product_price->value()) {
      $price = $wrapper->field_product_price->value();
      $price_formatted = number_format($price, 0, ',', ' ') . '&nbspKč';
    }

    if(!empty($price)) {
      $data = [];
      $data['price'] = $price;
      $data['price_formatted'] = $price_formatted;
      $data['morelink'] = url('node/16');

      $content .= theme('customize_product_price', array('data' => $data));
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

function customize_product_tech_render($field, $title = NULL) {
  $content = '';

    try {

      $node = $field['entity'];
      $wrapper = entity_metadata_wrapper('node', $field['entity']);

      $tech = [];
      foreach ($wrapper->field_product_tech->getIterator() as $delta => $product_wrapper) {
        $tech[] = [
          'nid' => $product_wrapper->getIdentifier(),
          'title' => $product_wrapper->label(),
          'body' => $product_wrapper->body->value()['safe_value'],
        ];
      }

      if(count($tech)) {
        $data = [];
        $data['tech'] = $tech;
        $content .= theme('customize_product_tech', array('data' => $data));
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

function customize_product_params_render($field, $title = NULL) {
  $content = '';

  try {

    $node = $field['entity'];
    $wrapper = entity_metadata_wrapper('node', $field['entity']);
    $table = $wrapper->field_product_params->value();

    if($table) {
      $items = [];
      if(isset($table['tabledata'])) {
        foreach ($table['tabledata'] as $data) {
          if(!empty($data[0]) && !empty($data[1])) {
            $items[] = [
              'title' => $data[0],
              'value' => $data[1],
            ];
          }
        }
      }

      $divider = ceil(count($items)/2);

      if(count($items)) {
        $content .= '<h3><span>Specifikace</span></h3>';
        $content .= '<div class="item-list">';
        $content .= '<div class="item-group">';
        $i = 0;
        foreach ($items as $item) {
          $i++;
          if($i <= $divider) {
            $content .= '<div class="item">';
            $content .= '<div class="title">';
            $content .= $item['title'];
            $content .= '</div>';
            $content .= '<div class="value">';
            $content .= $item['value'];
            $content .= '</div>';
            $content .= '</div>';
          }
        }
        $content .= '</div>';

        $content .= '<div class="item-group">';
        $i = 0;
        foreach ($items as $item) {
          $i++;
          if($i > $divider) {
            $content .= '<div class="item">';
            $content .= '<div class="title">';
            $content .= $item['title'];
            $content .= '</div>';
            $content .= '<div class="value">';
            $content .= $item['value'];
            $content .= '</div>';
            $content .= '</div>';
          }
        }
        $content .= '</div>';
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

function customize_product_subtitle_render($field, $title = NULL) {

  $content = '';

  try {

    $node = $field['entity'];
    $wrapper = entity_metadata_wrapper('node', $field['entity']);

    $term = $wrapper->field_product_category->value();
    $depth = taxonomy_term_depth_get_by_tid($term->tid); // check depth level
    if($depth == 3) {
      $content .= $term->name;
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

function customize_product_highlight_render($field, $title = NULL) {

  $content = '';

  try {

    $node = $field['entity'];
    $wrapper = entity_metadata_wrapper('node', $field['entity']);

    if($wrapper->field_product_highlight->value()) {
      $content .= '<div class="highlight highlight-' . $wrapper->field_product_highlight->raw() . '">' . $wrapper->field_product_highlight->label() . '</div>';
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

function customize_product_related_render($field, $title = NULL) {

  $content = '';

  try {

    $node = $field['entity'];
    $wrapper = entity_metadata_wrapper('node', $field['entity']);

    $product = [];
    // exclude from our db query
    $nid_exclude = [$wrapper->getIdentifier()];

    // first add related products
    foreach ($wrapper->field_product_related as $delta => $product_wrapper) {
      // avoid loop if referenced same product
      if($product_wrapper->getIdentifier() == $wrapper->getIdentifier()) {
        continue;
      }
      $view = node_view($product_wrapper->value(), 'teaser');
      $product[] = array(
        'nid' => $product_wrapper->getIdentifier(),
        'node' => drupal_render($view),
      );
      $nid_exclude[] = $product_wrapper->getIdentifier();

    }
    // select all products except related and parent
    $query = new EntityFieldQuery();

    $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'product')
      ->propertyCondition('status', NODE_PUBLISHED)
      ->propertyCondition('nid', $nid_exclude, 'NOT IN');

    $result = $query->execute();
    if (isset($result['node'])) {

      $nids = array_keys($result['node']);
      // random product order
      shuffle($nids);

      $items = entity_load('node', $nids);

      foreach ($items as $item) {
        // fill with products to 4 items
        if(count($product) < 4) {
          $product_wrapper = entity_metadata_wrapper('node', $item);
          $view = node_view($product_wrapper->value(), 'teaser');
          $product[] = array(
            'nid' => $product_wrapper->getIdentifier(),
            'node' => drupal_render($view),
          );
        }
      }

    }

    if(count($product)) {
      $content .= '<h2><span>Mohlo by vás zajímat</span></h2>';
      $content .= '<div class="row item-list">';
      foreach ($product as $product_item) {
        $content .= '<div class="col-sm-3 col-xs-12 item">';
        $content .= $product_item['node'];
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

function customize_product_category_title_render($field, $title = NULL) {

  $content = '';

  try {

    $node = $field['entity'];
    $wrapper = entity_metadata_wrapper('taxonomy_term', $field['entity']);
    $depth = taxonomy_term_depth_get_by_tid($wrapper->getIdentifier()); // check depth level
    $title = $wrapper->label();
    $image = $wrapper->field_term_image->value();

    if($depth == 1 && $image) {
      $path = file_create_url($image['uri']);
      $content .= '<h1 class="page-header page-header-image" style="background-image: url(' . $path . ')"><span>' . $title . '</span></h1>';
    }else{
      $content .= '<h1 class="page-header"><span>' . $title . '</span></h1>';
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

function customize_paragraph_timeline_render($field, $title = NULL) {

  $content = '';

  try {

    $node = $field['entity'];
    $wrapper = entity_metadata_wrapper('paragraphs_item', $field['entity']);

    $content .= '<h2><span>Historie</span></h2>';
    $content .= '<ul>';
    foreach ($wrapper->field_paragraph_timeline->getIterator() as $delta => $item_wrapper) {
      $image = $item_wrapper->field_timeline_image->value();
      $class = [];
      if($delta%2 == 0) {
        $class[] = 'bounceInLeft';
      }else{
        $class[] = 'bounceInRight';
      }
      $content .= '<li class="' . implode($class, ' ') . '">';
      $content .= '<div class="year">';
      $content .= $item_wrapper->field_timeline_year->value();
      $content .= '</div>';
      $content .= '<div class="description">';
      if($image) {
        $content .= '<div class="image">';
        $content .= theme('image_style', array('style_name' => 'timeline-list', 'path' => $image['uri']));
        $content .= '</div>';
      }
      $content .= '<div class="text">';
      $content .= $item_wrapper->field_timeline_body->value()['safe_value'];
      $content .= '</div>';
      $content .= '</div>';
      $content .= '</li>';
    }
    $content .= '</ul>';

  }catch (EntityMetadataWrapperException $exc) {
    watchdog(
      'customize',
      'See '  . __FUNCTION__ . '() <pre>' .  $exc->getTraceAsString() . '</pre>',
       NULL, WATCHDOG_ERROR
    );
  }

  return $content;

}
