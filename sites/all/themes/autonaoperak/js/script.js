(function ($) {

  Drupal.behaviors.autonaoperak = {
    attach: function (context, settings) {

      // add class external to external links
      $('a').filter(function() {
         return this.hostname && this.hostname !== location.hostname;
      }).addClass('external');

      // menu on mobile/tablet
      $('.navbar-toggle').on('click',function ( event ) {
        $('.navbar').toggleClass('open');
      });

      // dynamically disable/enable iframe move
      $gooogle_maps = $('.embed-responsive.google-maps-js');
      $('iframe', $gooogle_maps).addClass('disable-iframe-move-js');
      $gooogle_maps.on('click', function () {
        $('iframe', this).removeClass('disable-iframe-move-js');
      });

      $gooogle_maps.mouseleave(function () {
        $('iframe', this).addClass('disable-iframe-move-js');
      });

      //toggle accordion up/down icon eg. faq section
      $('.panel-group .panel-collapse').on('hide.bs.collapse', function () {
        var $link = $(this).closest('.panel').find('.panel-title a');
        $link.find('.glyphicon').toggleClass('glyphicon-menu-down glyphicon-menu-up');
        $link.removeClass('open');
      })
      $('.panel-group .panel-collapse').on('show.bs.collapse', function () {
        var $link = $(this).closest('.panel').find('.panel-title a');
        $link.find('.glyphicon').toggleClass('glyphicon-menu-down glyphicon-menu-up');
        $link.addClass('open');
      })

    }
  };

})(jQuery);
