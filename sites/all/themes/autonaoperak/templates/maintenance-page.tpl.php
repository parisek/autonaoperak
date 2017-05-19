<?php

/**
 * @file
 * Default theme implementation to display a single Drupal page while offline.
 *
 * All the available variables are mirrored in html.tpl.php and page.tpl.php.
 * Some may be blank but they are provided for consistency.
 *
 * @see template_preprocess()
 * @see template_preprocess_maintenance_page()
 *
 * @ingroup themeable
 */
?>
<!DOCTYPE html>
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>">

<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <?php print $head; ?>
  <title><?php print $head_title; ?></title>
  <?php print $styles; ?>
  <?php print $scripts; ?>
</head>
<body class="<?php print $classes; ?>">
  <header id="navbar" role="banner" class="header">
    <div class="container">
      <div class="block-logo">
        <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>">
          <img src="<?php print $base_path . $directory; ?>/logo.svg" alt="<?php print t('Home'); ?>" class="img-responsive">
        </a>
      </div>
    </div>
  </header>
  <div class="main-content">
    <div class="container">
      <?php if (!empty($title)): ?>
        <h1 class="page-header"><?php print $title; ?></h1>
      <?php endif; ?>
      <?php print $messages; ?>
      <?php print $content; ?>
    </div>
  </div>

</body>
</html>
