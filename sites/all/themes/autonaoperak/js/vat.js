(function ($) {

  Drupal.behaviors.autonaoperak_vat = {
    attach: function (context, settings) {

      function number_format(number) {
        if (typeof number != 'undefined') {
          number = Math.round(number);
          return number.toString().replace(/\B(?=(\d{3})+(?!\d))/g, " ") + ' Kč';
        }
      }

      var STORAGE_KEY = 'vat_included';

      $('.block-header-vat').once('block-header-vat', function() {

        let $block = $('.block-header-vat');
        let included = Cookies.get(STORAGE_KEY);
        if (typeof included !== 'undefined') {
          if(included === 'true') {
            $('.vat-included', $block).prop('checked', true);
          }else{
            $('.vat-excluded', $block).prop('checked', true);
          }
        }else{
          Cookies.set(STORAGE_KEY, 'false', { path: '/', expires: 365 });
        }
        toggleVat();

        $('input[type="radio"]', $block).on('change', function() {
          let $value = $('input[type="radio"]:checked', $block);
          let includedCurrent = 'false';
          if($value.val() == 1) {
            includedCurrent = 'true';
          }
          let includedCookie = Cookies.get(STORAGE_KEY);
          if(includedCookie != includedCurrent) {
            Cookies.set(STORAGE_KEY, includedCurrent, { path: '/', expires: 365 });
            recalculateViewFilters();
          }
          toggleVat();
        });

      });

      function toggleVat() {

        let included = Cookies.get(STORAGE_KEY);
        $('.js-car-price').each(function() {
          let $this = $(this);
          let price = $this.data('price');
          let price_vat = $this.data('price-vat');
          let symbol = $this.data('symbol');
          if(included === 'true') {
            $this.html(accounting.formatMoney(price_vat, '&nbsp;' + symbol, 0, '&nbsp;', ',', '%v%s'));
          }else{
            $this.html(accounting.formatMoney(price, '&nbsp;' + symbol, 0, '&nbsp;', ',', '%v%s'));
          }
        });

        if(included === 'true') {
          $('.js-car-note-vat').removeClass('hide');
          $('.js-car-note-without-vat').addClass('hide');
        }else{
          $('.js-car-note-without-vat').removeClass('hide');
          $('.js-car-note-vat').addClass('hide');
        }

      }

      function recalculateViewFilters() {

        // when changed reset pricing field because we are filtering based on non vat prices
        $view = $('.view-block-car-list');
        if($view.length) {
          $('#edit-field-price-from-value-min', $view).val(0);
          $('#edit-field-price-from-value-max', $view).val(50000);
          $('.view-filters .form-submit', $view).trigger('click');
          $('.category-list-form .slider-from').text(number_format(0));
          $('.category-list-form .slider-to').text(number_format(50000));
          $('.category-list-form input.input-slider').slider('setValue', [0, 50000]);
        }

      }

    }
}

})(jQuery);
