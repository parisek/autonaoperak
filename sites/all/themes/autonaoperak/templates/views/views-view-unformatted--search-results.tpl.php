<?php

/**
 * @file
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */
$count = count($rows);
$number = 1;
?>
<?php if (!empty($title)): ?>
  <h3><?php print $title; ?></h3>
<?php endif; ?>
<div class="row">
<?php foreach ($rows as $id => $row): ?>
  <?php
  $class = [];
  if($number > ($count-4)) {
    $class[] = 'last-row';
  }
  ?>
  <div<?php if ($classes_array[$id]) { print ' class="' . $classes_array[$id] . ' ' . implode(' ', $class) . '"';  } ?>>
    <?php print $row; ?>
  </div>
  <?php
  if($number%4 == 0) {
    print '<div class="col-xs-12 visible-lg visible-md"></div>';
  }
  if($number%3 == 0) {
    print '<div class="col-xs-12 visible-sm"></div>';
  }
  $number++;
  ?>
<?php endforeach; ?>
</div>
