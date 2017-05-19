<?php

/**
 * @file
 * Display Suite 2 column template.
 */
?>
<<?php print $layout_wrapper; print $layout_attributes; ?> class="ds-2col <?php print $classes;?> clearfix">

  <?php if (isset($title_suffix['contextual_links'])): ?>
  <?php print render($title_suffix['contextual_links']); ?>
  <?php endif; ?>
  <?php if($left_classes != ''): ?>
    <<?php print $left_wrapper ?> class="<?php print trim($left_classes); ?>">
  <?php else: ?>
    <<?php print $left_wrapper ?> class="group-left">
  <?php endif; ?>
    <?php print $left; ?>
  </<?php print $left_wrapper ?>>

  <?php if($right_classes != ''): ?>
    <<?php print $right_wrapper ?> class="<?php print trim($right_classes); ?>">
  <?php else: ?>
    <<?php print $right_wrapper ?> class="group-right">
  <?php endif; ?>
    <?php print $right; ?>
  </<?php print $right_wrapper ?>>

</<?php print $layout_wrapper ?>>

<?php if (!empty($drupal_render_children)): ?>
  <?php print $drupal_render_children ?>
<?php endif; ?>
