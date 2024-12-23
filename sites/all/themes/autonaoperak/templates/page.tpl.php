<?php
/**
 * @file
 * Default theme implementation to display a single Drupal page.
 *
 * The doctype, html, head and body tags are not in this template. Instead they
 * can be found in the html.tpl.php template in this directory.
 *
 * Available variables:
 *
 * General utility variables:
 * - $base_path: The base URL path of the Drupal installation. At the very
 *   least, this will always default to /.
 * - $directory: The directory the template is located in, e.g. modules/system
 *   or themes/bartik.
 * - $is_front: TRUE if the current page is the front page.
 * - $logged_in: TRUE if the user is registered and signed in.
 * - $is_admin: TRUE if the user has permission to access administration pages.
 *
 * Site identity:
 * - $front_page: The URL of the front page. Use this instead of $base_path,
 *   when linking to the front page. This includes the language domain or
 *   prefix.
 * - $logo: The path to the logo image, as defined in theme configuration.
 * - $site_name: The name of the site, empty when display has been disabled
 *   in theme settings.
 * - $site_slogan: The slogan of the site, empty when display has been disabled
 *   in theme settings.
 *
 * Navigation:
 * - $main_menu (array): An array containing the Main menu links for the
 *   site, if they have been configured.
 * - $secondary_menu (array): An array containing the Secondary menu links for
 *   the site, if they have been configured.
 * - $breadcrumb: The breadcrumb trail for the current page.
 *
 * Page content (in order of occurrence in the default page.tpl.php):
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title: The page title, for use in the actual HTML content.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 * - $messages: HTML for status and error messages. Should be displayed
 *   prominently.
 * - $tabs (array): Tabs linking to any sub-pages beneath the current page
 *   (e.g., the view and edit tabs when displaying a node).
 * - $action_links (array): Actions local to the page, such as 'Add menu' on the
 *   menu administration interface.
 * - $feed_icons: A string of all feed icons for the current page.
 * - $node: The node object, if there is an automatically-loaded node
 *   associated with the page, and the node ID is the second argument
 *   in the page's path (e.g. node/12345 and node/12345/revisions, but not
 *   comment/reply/12345).
 *
 * Regions:
 * - $page['help']: Dynamic help text, mostly for admin pages.
 * - $page['highlighted']: Items for the highlighted content region.
 * - $page['content']: The main content of the current page.
 * - $page['sidebar_first']: Items for the first sidebar.
 * - $page['sidebar_second']: Items for the second sidebar.
 * - $page['header']: Items for the header region.
 * - $page['footer']: Items for the footer region.
 *
 * @see bootstrap_preprocess_page()
 * @see template_preprocess()
 * @see template_preprocess_page()
 * @see bootstrap_process_page()
 * @see template_process()
 * @see html.tpl.php
 *
 * @ingroup themeable
 */
?>
<header role="banner" class="header">
  <?php if (!empty($page['topbar'])): ?>
  <div class="topbar">
    <div class="container-fluid">
      <?php print render($page['topbar']); ?>
    </div>
  </div>
  <?php endif; ?>
  <nav class="navbar navbar-default navbar-fixed-top">
    <div class="container-fluid">
      <div class="region-header">
        <div class="block-logo">
          <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>">
            <img src="<?php print $base_path . $directory; ?>/logo-<?php print $language; ?>.svg" alt="<?php print t('Home'); ?>" class="img-responsive">
          </a>
          <?php if (!empty($page['navigation'])): ?>
            <button type="button" class="navbar-toggle collapsed" data-toggle="collapse" data-target=".navbar-collapse"><?php print t('Menu'); ?></button>
          <?php endif; ?>
        </div>
        <?php if (!empty($page['navigation'])): ?>
          <div class="block-main-menu">
            <?php if($cars_stock): ?>
            <style type="text/css">
              .block-main-menu ul.menu li.menu-580 a:after,
              .block-main-menu ul.menu li.menu-934 a:after {
                content: '<?php print $cars_stock; ?>'!important;
              }
            </style>
            <?php endif; ?>
            <div class="navbar-collapse collapse">
              <nav role="navigation">
                <?php print render($page['navigation']); ?>
              </nav>
          </div>
          </div>
        <?php endif; ?>
      </div>
    </div>
  </nav>
</header>
<div class="page-wrapper">
<?php if (!empty($page['content_above'])): ?>
  <div class="content-above">
    <?php print render($page['content_above']); ?>
  </div>
<?php endif; ?>

<div class="main-container">
  <div class="container">
    <div class="row">
      <?php if (!drupal_is_front_page()): ?>
        <div class="col-xs-12 hidden-print block-breadcrumbs">
        <?php if (!empty($breadcrumb)): print $breadcrumb; endif;?>
        </div>
      <?php endif; ?>
      <?php if (!empty($page['sidebar_first'])): ?>
        <aside class="col-md-3 hidden-sm hidden-xs sidebar-first" role="complementary">
          <?php print render($page['sidebar_first']); ?>
        </aside>  <!-- /#sidebar -->
      <?php endif; ?>
      <section class="<?php print $content_column_class_custom; ?>">
        <a id="main-content"></a>
        <?php print render($title_prefix); ?>
        <?php if (!empty($title)): ?>
          <h1 class="page-header"><span><?php print $title; ?></span></h1>
        <?php endif; ?>
        <?php print render($title_suffix); ?>
        <?php print $messages; ?>
        <?php if (!empty($tabs)): ?>
          <?php print render($tabs); ?>
        <?php endif; ?>
        <?php if (!empty($page['help'])): ?>
          <?php print render($page['help']); ?>
        <?php endif; ?>
        <?php if (!empty($action_links)): ?>
          <ul class="action-links"><?php print render($action_links); ?></ul>
        <?php endif; ?>
        <?php print render($page['content']); ?>
      </section>
      <?php if (!empty($page['sidebar_second'])): ?>
        <aside class="col-md-5 col-sm-12 sidebar-second" role="complementary">
          <?php print render($page['sidebar_second']); ?>
        </aside>  <!-- /#sidebar -->
      <?php endif; ?>
    </div>
  </div>
</div>
<?php if (!empty($page['content_below'])): ?>
  <div class="content-below">
    <a id="content-scroll"></a>
    <?php print render($page['content_below']); ?>
  </div>
<?php endif; ?>

<?php if (!empty($page['footer'])): ?>
  <footer class="footer">
    <div class="container">
    <?php print render($page['footer']); ?>
    </div>
  </footer>
<?php endif; ?>
</div>
