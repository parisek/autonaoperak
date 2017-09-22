(function ($) {

  Drupal.behaviors.autonaoperak_eucookie = {
    attach: function (context, settings) {

      eu_cookie = Cookies.get('eu_cookie');
      if (typeof eu_cookie === "undefined") {
        $('body').append('<div class="eu-cookies">' +
                         '<div class="container">' +
                         '<div class="row">' +
                         '<div class="col-sm-10 cookie-text"><div class="cookie-text-inner">' +
                         Drupal.t('This site uses cookies to optimize the efficient provision of services in accordance with the <a href="@url" target="_blank">cookies policy</a>. The conditions for storing or accessing cookies can be set in your browser.', {'@url': 'https://www.google.com/policies/technologies/cookies/'}, {context: 'autonaoperak:cookie'}) +
                         '</div></div>' +
                         '<div class="col-sm-2 cookie-button"><button type="button" class="btn btn-primary CookiesOK">' +
                         Drupal.t('Accept', {}, {context: 'autonaoperak:cookie'}) +
                         '</button></div>' +
                         '</div>' +
                         '</div>' +
                         '</div>');
        $eu_cookie = $('.eu-cookies');
        $eu_cookie.find('.CookiesOK').on('click', function() {
          Cookies.set('eu_cookie', true, { path: '/', expires: 365 });
          $eu_cookie.fadeTo( "slow" , 0, function() {
            $eu_cookie.remove();
          });
        });
      }

    }
}

})(jQuery);
