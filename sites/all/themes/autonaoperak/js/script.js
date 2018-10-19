(function ($) {

  Drupal.behaviors.autonaoperak = {
    attach: function (context, settings) {

      // Navbar scroll effect
      $(window).on('scroll load', function(event) {
        var scroll = $(window).scrollTop();

        if (scroll >= 10) {
            $(".navbar-default").addClass("is-scrolling");
        } else {
            $(".navbar-default").removeClass("is-scrolling");
        }
      });

      // add class external to external links
      $('a').filter(function() {
         return this.hostname && this.hostname !== location.hostname;
      }).addClass('external');

      // menu on mobile/tablet
      $('.navbar-toggle').on('click',function ( event ) {
        $('.navbar').toggleClass('open');
        $('body').toggleClass('navbar-open');
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

      if (window.matchMedia("(min-width: 769px)").matches) {
        var $slider = $('.slider-nav');
        var $owl = $('#main-slider');

        $owl.on('initialize.owl.carousel resize.owl.carousel', function(event) {
          var width = $(window).width()-$('.container', $slider).width();
          $('.gradient-left', $slider).css('width', width/2 + 'px');
          $('.gradient-right', $slider).css('width', width/2 + 'px');
        })

        $owl.owlCarousel({
          items:1,
          loop:true,
          margin:0,
          nav:true,
          navText: ['<span class="glyphicon glyphicon-chevron-left" aria-hidden="true"></span>', '<span class="glyphicon glyphicon-chevron-right" aria-hidden="true"></span>'],
          dots:true,
          lazyLoad:true,
          autoplay:true,
          autoplayTimeout:7000,
          autoplayHoverPause:true,
          dotsContainer: '#carousel-custom-dots',
        })

        $('.owl-dot').on('click', function () {
          $owl.trigger('to.owl.carousel', [$(this).index(), 300]);
        });
      }

      var $slider_offer = $('#offer-slider');
      $slider_offer.owlCarousel({
        loop:true,
        margin:0,
        nav:true,
        navText: ['<span class="glyphicon glyphicon-chevron-left" aria-hidden="true"></span>', '<span class="glyphicon glyphicon-chevron-right" aria-hidden="true"></span>'],
        dots:false,
        lazyLoad:true,
        autoplay:true,
        autoplayTimeout:5000,
        autoplayHoverPause:true,
        responsive:{
          0:{
              items:3
          },
          600:{
              items:4
          },
        }
      })

      var $slider_related = $('#related-slider');
      $slider_related.owlCarousel({
        loop:false,
        navRewind:false,
        margin:0,
        nav:true,
        navText: ['<span class="glyphicon glyphicon-chevron-left" aria-hidden="true"></span>', '<span class="glyphicon glyphicon-chevron-right" aria-hidden="true"></span>'],
        dots:false,
        lazyLoad:true,
        autoplay:true,
        autoplayTimeout:5000,
        autoplayHoverPause:true,
        responsive:{
          0:{
              items:3,
              loop:true,
              navRewind:true,
          },
          600:{
              items:4
          },
        }
      })

      //toggle accordion up/down icon eg. faq section
      $('.panel-group .panel-collapse').on('hide.bs.collapse', function () {
        var $link = $(this).closest('.panel').find('.panel-title a');
        $link.removeClass('open');
      })
      $('.panel-group .panel-collapse').on('show.bs.collapse', function () {
        var $link = $(this).closest('.panel').find('.panel-title a');
        $link.addClass('open');
      })

      // submenu open/close
      $submenu = $('.block-sidebar-category');
      $('ul.menu li span.submenu-toggle', $submenu).on('click', function(e) {
        e.preventDefault();
        var $parent = $(this).closest('li');
        if($parent.hasClass('open')) {
          $parent.removeClass('open');
          $parent.find('li').removeClass('open');
          $('span.submenu-toggle', $parent).removeClass('icon-up').addClass('icon-down');
        }else{
          $parent.addClass('open');
          $('span.submenu-toggle', $parent).removeClass('icon-down').addClass('icon-up');
        }
      });

      //links anchor on product detail page
      if($('.node').length) {
        $('.node a[href^="#"]').on('click',function ( event ) {
          var anchor = $(this).attr('href');
          if(anchor.length && $('[name=' + anchor.replace('#', '') + ']').length) {
            event.preventDefault();
            anchor = anchor.replace('#', '');
            $('html, body').animate({
                scrollTop: $('[name=' + anchor + ']').offset().top-50,
            }, 500, function(){
              $('#edit-submitted-name').focus();
            });
          }
        });
      }

      // HP Offer block to animate counting of stock cars
      var $offer = $('.block-hp-offer');
      if($offer.length) {
        var $counter = $('.count', $offer);
        var count = $counter.data('count');
        var options = {
          useEasing : true,
          useGrouping : true,
          separator : '',
          decimal : ',',
        };
        var countup = new CountUp('offer-count', 0, count, 0, 2.5, options);
        countup.start();
      }

      // Pricelist selector
      $( 'select#raid' ).on( 'change', function() {
        var raid = $( this ).val();
        $( '.pricelist .pricelist-item, .pricelist-mobile .pricelist-item' ).addClass('hide').removeClass('show');
        $( '.pricelist .pricelist-item-' + raid + ', .pricelist-mobile .pricelist-item-' + raid ).addClass('show').removeClass('hide');
      });

      $('.pricelist-select').on('inview', function(event, isInView) {
        if (isInView) {
          $('.pricelist-select').addClass('animated pulse');
        }else{
          $('.pricelist-select').removeClass('animated pulse');
        }
      });

    }
  };

})(jQuery);
