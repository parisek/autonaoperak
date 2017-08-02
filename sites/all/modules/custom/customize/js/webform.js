(function ($) {

  Drupal.behaviors.customize_webform = {
    attach: function (context, settings) {

      $.fn.customize_webform_submitted = function(form_id) {
         dataLayer.push({
           'event' : 'webformSubmitted',
           'eventCategory' : 'Form Submit',
           'eventAction' : 'Form Submit',
           'eventLabel' : 'Form Submit',
           'eventValue' : form_id
         });
      };

    }
  }

})(jQuery);
