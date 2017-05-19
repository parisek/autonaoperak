<?php

/**
 * Implements hook_token_info().
 */
function customize_token_info() {
  $info['tokens']['current-user']['customize'] = array(
    'name' => t('User host and browser'),
    'description' => t('Return user ip address and browser.'),
  );
  return $info;
}

/**
* Implements hook_tokens().
*/
function customize_tokens($type, $tokens, array $data = array(), array $options = array()) {
  $sanitize = !empty($options['sanitize']);

  $replacements = array();
  if ($type == 'user') {
    foreach ($tokens as $name => $original) {
      switch ($name) {
        // Basic user account information.
        case 'customize':
          $ip = ip_address();
          $hostname = gethostbyaddr($ip);
          $host = $ip . ' ' . $hostname . ' ' . $_SERVER['HTTP_USER_AGENT'];
          $replacements[$original] = $sanitize ? check_plain($host) : $host;
          break;
      }
    }
  }

  return $replacements;
}
