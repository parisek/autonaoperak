(function ($) {

  Drupal.behaviors.customize_product_list = {
    attach: function (context, settings) {

      function number_format(number) {
        if (typeof number != 'undefined') {
          number = Math.round(number);
          return number.toString().replace(/\B(?=(\d{3})+(?!\d))/g, " ") + ' Kč';
        }
      }

      var $filter = $('.category-list-form', context);

      // if parameter passed from URL
      var fuel = $('.view-block-car-list #edit-field-car-fuel-value');
      if(fuel.val()) {
        fuel = fuel.val();
        $('.item-fuel input[type=checkbox]', $filter).each(function() {
          if(fuel.indexOf($(this).val()) !== -1) {
            $(this).attr('checked', 'checked');
          }
        });
      }
      $('.item-fuel input[type=checkbox]', $filter).on('change', function() {
        var items = [];
        $('.item-fuel input[type=checkbox]:checked', $filter).each(function() {
          items.push($(this).val());
        });
        $('.view-block-car-list #edit-field-car-fuel-value').val(items);

        $('.view-block-car-list .view-filters .form-submit').trigger('click');
      });

      // if parameter passed from URL
      var trans = $('.view-block-car-list #edit-field-car-transmission-value');
      if(trans.val()) {
        trans = trans.val();
        $('.item-transmission input[type=checkbox]', $filter).each(function() {
          if(trans.indexOf($(this).val()) !== -1) {
            $(this).attr('checked', 'checked');
          }
        });
      }
      $('.item-transmission input[type=checkbox]', $filter).on('change', function() {
        var items = [];
        $('.item-transmission input[type=checkbox]:checked', $filter).each(function() {
          items.push($(this).val());
        });
        $('.view-block-car-list #edit-field-car-transmission-value').val(items);

        $('.view-block-car-list .view-filters .form-submit').trigger('click');
      });

      var body = $('.view-block-car-list #edit-field-car-body-value').val();
      if(body != 'All') {
        $('.item-body select', $filter).val(body);
      }
      $('.item-body select', $filter).on('change', function(event) {
        var $this = $(this);
        $('.view-block-car-list #edit-field-car-body-value').val($this.val());

        $('.view-block-car-list .view-filters .form-submit').trigger('click');
      });

      $('.item-sort input[type=radio],.item-sort select', $filter).on('change', function(event) {
        var type = $(this).val();
        var $orderby = $('.view-block-car-list #edit-sort-by'); // field_price_from_value, field_weight_value
        var $order = $('.view-block-car-list #edit-sort-order'); // ASC, DESC

        if(type == 'recommended') {
          $orderby.val('field_weight_value');
          $order.val('ASC');
        }else if(type == 'cheapest') {
          $orderby.val('field_price_from_value');
          $order.val('ASC');
        }else if(type == 'expensive') {
          $orderby.val('field_price_from_value');
          $order.val('DESC');
        }

        $('.view-block-car-list .view-filters .form-submit').trigger('click');
      });

      $('.item-price #price-from', $filter).on('keyup change paste', function(event) {
        var value = $(this).val();
        $('.view-block-car-list #edit-field-price-from-value-min').val(value);
      });
      $('.item-price #price-to', $filter).on('keyup change paste', function(event) {
        var value = $(this).val();
        $('.view-block-car-list #edit-field-price-from-value-max').val(value);
      });

      $('.form-submit', $filter).on('click', function(e) {
        e.preventDefault();
        $('.view-block-car-list .view-filters .form-submit').trigger('click');
      });

      // listen for ajax request and add opacity effect
      $(document).ajaxStart(function() {
        $('div.view', context).addClass('view-refresh');
      });
      $(document).ajaxSuccess(function(){
         $('div.view', context).removeClass('view-refresh');
      });

      // toggle text for morelink button
      $('#categoryAdvancedFilters', $filter).on('show.bs.collapse', function () {
        $('.morelink .text', $filter).text('Skrýt rozšířené filtry');
      })
      $('#categoryAdvancedFilters', $filter).on('hide.bs.collapse', function () {
        $('.morelink .text', $filter).text('Zobrazit rozšířené filtry');
      })

      $('input.input-slider', $filter).slider({
        tooltip_split: true,
        handle: 'square',
        tooltip: 'hide'
      })

      // load price value from URL
      // useful when hitting back button
      var price_from = parseInt($('.view-block-car-list #edit-field-price-from-value-min').val());
      var price_to = parseInt($('.view-block-car-list #edit-field-price-from-value-max').val());
      if(price_from>0 || price_to>0) {
        $('.slider-from', $filter).text(number_format(price_from));
        $('.slider-to', $filter).text(number_format(price_to));
        $('input.input-slider', $filter).slider('setValue', [price_from, price_to]);
      }

      // define outside of scope
      var submitTimeout = '';

      $('input.input-slider', $filter).on('slide', function(event) {
        var from = event.value[0];
        var to = event.value[1];
        // show to user
        $('.slider-from', $filter).text(number_format(from));
        $('.slider-to', $filter).text(number_format(to));
        // pass to view
        $('.view-block-car-list #edit-field-price-from-value-min').val(from);
        $('.view-block-car-list #edit-field-price-from-value-max').val(to);

        // Reset timelimit
        clearTimeout(submitTimeout);

        // Delay submit for 1s to allow tuning of pricing
        submitTimeout = setTimeout(function() {
          $('.view-block-car-list .view-filters .form-submit').trigger('click');
        }, 1000);

      });

      if (window.matchMedia("(max-width: 768px)").matches) {
        $('#categoryMobileFilters', $filter).addClass('collapse');
      }

      // toggle text for mobile morelink button
      $('#categoryMobileFilters', $filter).on('hide.bs.collapse', function () {
        $('.morelink-mobile .text', $filter).text('Zobrazit filtry');
      })
      $('#categoryMobileFilters', $filter).on('show.bs.collapse', function () {
        $('.morelink-mobile .text', $filter).text('Skrýt filtry');
      })

    }
  }

})(jQuery);
