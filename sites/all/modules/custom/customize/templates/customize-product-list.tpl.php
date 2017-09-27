<div class="category-list-form">
  <div class="category-list-filter">
    <div id="categoryMobileFilters">
    <h2 class="hidden-xs"><?php print t('Choose a car to your liking'); ?></h2>
      <div class="item-list">
        <?php if(count($data['form_fuel'])): ?>
        <div class="item item-fuel">
          <label><?php print t('Fuel'); ?></label>
          <div class="select-background">
          <select class="form-control">
            <?php foreach($data['form_fuel'] as $key => $name): ?>
            <option value="<?php print $key; ?>"><?php print $name; ?></option>
            <?php endforeach; ?>
          </select>
          </div>
        </div>
        <?php endif; ?>
        <?php if(count($data['form_transmission'])): ?>
        <div class="item item-transmission">
          <label><?php print t('Transmission'); ?></label>
          <div class="btn-group" role="group" aria-label="<?php print t('Transmission'); ?>">
            <?php foreach($data['form_transmission'] as $key => $name): ?>
            <label class="btn btn-default"><input type="checkbox" name="fuel[]" value="<?php print $key; ?>"><span><?php print $name; ?></span></label>
            <?php endforeach; ?>
          </div>
        </div>
        <?php endif; ?>
        <?php if(count($data['form_body'])): ?>
        <div class="item item-body">
          <label><?php print t('Body type'); ?></label>
          <div class="select-background">
          <select class="form-control">
            <?php foreach($data['form_body'] as $key => $name): ?>
            <option value="<?php print $key; ?>"><?php print $name; ?></option>
            <?php endforeach; ?>
          </select>
          </div>
        </div>
        <?php endif; ?>
        <div class="item item-sort">
          <label><?php print t('Sort by'); ?></label>
          <div class="select-background">
          <select class="form-control">
            <option value="recommended" checked="checked"><?php print t('Recommended'); ?></option>
            <option value="cheapest"><?php print t('From cheapest'); ?></option>
            <option value="expensive"><?php print t('From most expensive'); ?></option>
          </select>
          </div>
        </div>
        <div class="item item-action">
          <a href="#" class="btn btn-primary btn-lg form-submit"><?php print t('Filter cars'); ?></a>
        </div>
        <div class="item item-advanced collapse" id="categoryAdvancedFilters">
          <div class="item-price">
            <div class="slider-wrapper">
              <input type="text" name="price" class="input-slider" value="" data-slider-min="0" data-slider-max="50000" data-slider-step="1000" data-slider-value="[0,50000]">
              <div class="info">
                <div class="slider-from">0 <?php print $data['currency_symbol']; ?></div>
                <div class="slider-to">50 000 <?php print $data['currency_symbol']; ?></div>
              </div>
            </div>
          </div>
        </div>
      </div>
    </div>
    <div class="morelink"><a role="button" data-toggle="collapse" href="#categoryAdvancedFilters" aria-expanded="false" aria-controls="categoryAdvancedFilters"><span class="icon-advanced"></span> <span class="text"><?php print t('Show more filters'); ?></span></a></div>
    <div class="morelink-mobile"><a role="button" data-toggle="collapse" href="#categoryMobileFilters" aria-expanded="false" aria-controls="categoryMobileFilters"><span class="icon-advanced"></span> <span class="text"><?php print t('Show filters'); ?></span></a></div>
  </div>
  <div class="category-list-sort">
    <div class="item item-sort">
      <ul>
        <li><label><input type="radio" name="sortby" value="recommended" checked="checked"><span><?php print t('Recommended'); ?></span></label></li>
        <li><label><input type="radio" name="sortby" value="cheapest"><span><?php print t('From cheapest'); ?></span></label></li>
        <li><label><input type="radio" name="sortby" value="expensive"><span><?php print t('From most expensive'); ?></span></label></li>
      </li>
    </div>
  </div>
</div>
<?php print $data['product_list']; ?>
