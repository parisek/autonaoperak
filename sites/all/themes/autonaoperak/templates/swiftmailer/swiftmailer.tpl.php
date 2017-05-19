<?php

/**
 * @file
 * Default theme implementation to format an HTML mail.
 *
 * Copy this file in your default theme folder to create a custom themed mail.
 * Rename it to mimemail-message--[module]--[key].tpl.php to override it for a
 * specific mail.
 *
 * Available variables:
 * - $recipient: The recipient of the message
 * - $subject: The message subject
 * - $body: The message body
 * - $css: Internal style sheets
 * - $module: The sending module
 * - $key: The message identifier
 *
 * @see template_preprocess_mimemail_message()
 */
$logo = url('<front>', array('absolute' => TRUE)) . path_to_theme() . '/templates/swiftmailer/logo.png';
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
  <head>
    <meta name="viewport" content="width=device-width" />
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <style type="text/css">
      <!--
      * {
        margin: 0;
        padding: 0;
        font-family: "Helvetica Neue", Helvetica, Arial, "Lucida Grande", sans-serif;
        font-size: 100%;
        line-height: 1.6;
      }
      img {
        max-width: 100%;
      }
      body {
        -webkit-font-smoothing: antialiased;
        -webkit-text-size-adjust: none;
        width: 100%!important;
        height: 100%;
      }
      h1, h2, h3, h4, h5, h6 {
        font-family: "Helvetica Neue", Helvetica, Arial, "Lucida Grande", sans-serif;
        color: #000;
        margin: 10px 0 10px;
        line-height: 1.2;
        font-weight: 200;
      }
      h1 {
        font-size: 150%;
      }
      h2 {
        font-size: 140%;
      }
      h3 {
        font-size: 130%;
      }
      h4 {
        font-size: 120%;
      }
      p, table {
        margin-bottom: 10px;
        font-weight: normal;
        font-size: 100%;
      }
      ul, ol {
        margin: 0 0 20px 0!important;
        padding: 0!important;
      }
      ul li, ol li {
        margin: 0!important;
        padding: 0!important;
        list-style: none;
        font-size: 90%;
      }
      -->
    </style>
  </head>
<body bgcolor="#f6f6f6" style="-webkit-font-smoothing: antialiased;-webkit-text-size-adjust: none;width: 100%!important;height: 100%;">
<!-- header -->
<table class="header-wrap" style="width: 100%;clear: both!important;">
  <tr>
    <td></td>
    <td class="container" style="display: block!important;max-width: 600px!important;margin: 0 auto!important;clear: both!important;">

      <!-- content -->
      <div class="content">
        <table style="width: 100%;">
          <tr>
            <td align="center">
              <p><a href="<?php print url('<front>', array('absolute' => TRUE)); ?>"><img src="<?php print $logo; ?>" title="Autonaoperak.cz" alt="Autonaoperak.cz" class="logo" width="303" height="63" /></a></p>
            </td>
          </tr>
        </table>
      </div>
      <!-- /content -->

    </td>
    <td></td>
  </tr>
</table>
<!-- /header -->
<!-- body -->
<table class="body-wrap" bgcolor="#f6f6f6" style="padding: 20px;width: 100%;mso-table-lspace:0pt;mso-table-rspace:0pt;">
<tr>
  <td></td>
  <td class="container" bgcolor="#FFFFFF" style="border: 1px solid #f0f0f0;padding: 20px;display: block!important;max-width: 600px!important;margin: 0 auto!important;clear: both!important;">
      <!-- content -->
      <div class="content">
      <table style="width: 100%;">
        <tr>
          <td>
          <?php print $body ?>
          </td>
        </tr>
      </table>
      </div>
      <!-- /content -->
      </td>
    <td></td>
  </tr>
</table>
<!-- /body -->

</body>
</html>
