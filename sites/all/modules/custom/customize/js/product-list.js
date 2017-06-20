(function ($) {

  Drupal.behaviors.customize_product_list = {
    attach: function (context, settings) {

      var $filter = $('.category-list-form', context);

      $('.item-fuel input[type=checkbox]', $filter).on('change', function() {
        var items = [];
        $('.item-fuel input[type=checkbox]:checked', $filter).each(function() {
          items.push($(this).val());
        });
        $('.view-block-car-list #edit-field-car-fuel-value').val(items);

        $('.view-block-car-list .view-filters .form-submit').trigger('click');
      });

      $('.item-transmission input[type=checkbox]', $filter).on('change', function() {
        var items = [];
        $('.item-transmission input[type=checkbox]:checked', $filter).each(function() {
          items.push($(this).val());
        });
        $('.view-block-car-list #edit-field-car-transmission-value').val(items);

        $('.view-block-car-list .view-filters .form-submit').trigger('click');
      });

      $('.item-body select', $filter).on('change', function(event) {
        var $this = $(this);
        $('.view-block-car-list #edit-field-car-body-value').val($this.val());

        $('.view-block-car-list .view-filters .form-submit').trigger('click');
      });

      $('.item-sort input[type=radio]', $filter).on('change', function(event) {
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

    }
  }

})(jQuery);
