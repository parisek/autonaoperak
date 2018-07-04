(function ($) {

  Drupal.behaviors.autonaoperak_vat = {
    attach: function (context, settings) {

      var STORAGE_KEY = 'vat_included';

      $block = $('.block-header-vat', context);
      if($block.length) {
        $('input[type="radio"]', $block).on('change', function() {
          let value = false;
          if($(this).val() == 1) {
            value = true;
          }
          Cookies.set(STORAGE_KEY, value, { path: '/', expires: 365 });
          toggleVat(value);
        });

        let included = Cookies.get(STORAGE_KEY);
        if (typeof included !== 'undefined') {
          $('input[type="radio"]', $block).prop('checked', included).trigger('change');
        }
      }

      function toggleVat(included) {
        $('.js-car-price').each(function() {
          let $this = $(this);
          let price = $this.data('price');
          let price_vat = $this.data('price-vat');
          let symbol = $this.data('symbol');
          if(included) {
            $this.text(accounting.formatMoney(price_vat, ' ' + symbol, 0, ' ', ',', '%v%s'));
          }else{
            $this.text(accounting.formatMoney(price, ' ' + symbol, 0, ' ', ',', '%v%s'));
          }
        });

        if(included) {
          $('.js-car-note-vat').removeClass('hide');
          $('.js-car-note-without-vat').addClass('hide');
        }else{
          $('.js-car-note-without-vat').removeClass('hide');
          $('.js-car-note-vat').addClass('hide');
        }
      }

    }
}

})(jQuery);
