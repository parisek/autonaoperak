<?php

/**
 * @file
 * Display Suite 2 column stacked template.
 */
?>
<<?php print $layout_wrapper; print $layout_attributes; ?> class="ds-2col-stacked <?php print $classes;?> clearfix">

  <?php if (isset($title_suffix['contextual_links'])): ?>
  <?php print render($title_suffix['contextual_links']); ?>
  <?php endif; ?>

  <?php if($header_classes != ''): ?>
    <<?php print $header_wrapper ?> class="<?php print $header_classes; ?>">
  <?php else: ?>
    <<?php print $header_wrapper ?> class="group-header">
  <?php endif; ?>
    <?php print $header; ?>
  </<?php print $header_wrapper ?>>

  <?php if($left_classes != ''): ?>
    <<?php print $left_wrapper ?> class="<?php print $left_classes; ?>">
  <?php else: ?>
    <<?php print $left_wrapper ?> class="group-left">
  <?php endif; ?>
    <?php print $left; ?>
  </<?php print $left_wrapper ?>>

  <?php if($right_classes != ''): ?>
    <<?php print $right_wrapper ?> class="<?php print $right_classes; ?>">
  <?php else: ?>
    <<?php print $right_wrapper ?> class="group-right">
  <?php endif; ?>
    <?php print $right; ?>
  </<?php print $right_wrapper ?>>

  <?php if($footer_classes != ''): ?>
    <<?php print $footer_wrapper ?> class="<?php print $footer_classes; ?>">
  <?php else: ?>
    <<?php print $footer_wrapper ?> class="group-footer">
  <?php endif; ?>
    <?php print $footer; ?>
  </<?php print $footer_wrapper ?>>

</<?php print $layout_wrapper ?>>

<?php if (!empty($drupal_render_children)): ?>
  <?php print $drupal_render_children ?>
<?php endif; ?>
