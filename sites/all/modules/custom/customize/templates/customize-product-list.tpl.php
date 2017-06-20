<div class="category-list-form">
  <div class="category-list-filter">
    <h2>Vyberte si vůz podle vašich představ</h2>
    <div class="item-list">
      <?php if(count($data['form_fuel'])): ?>
      <div class="item item-fuel">
        <label>Palivo</label>
        <div class="btn-group" role="group" aria-label="Palivo">
          <?php foreach($data['form_fuel'] as $key => $name): ?>
          <label class="btn btn-default"><input type="checkbox" name="fuel[]" value="<?php print $key; ?>"><span><?php print $name; ?></span></label>
          <?php endforeach; ?>
        </div>
      </div>
      <?php endif; ?>
      <?php if(count($data['form_transmission'])): ?>
      <div class="item item-transmission">
        <label>Převodovka</label>
        <div class="btn-group" role="group" aria-label="Převodovka">
          <?php foreach($data['form_transmission'] as $key => $name): ?>
          <label class="btn btn-default"><input type="checkbox" name="fuel[]" value="<?php print $key; ?>"><span><?php print $name; ?></span></label>
          <?php endforeach; ?>
        </div>
      </div>
      <?php endif; ?>
      <?php if(count($data['form_body'])): ?>
      <div class="item item-body">
        <label>Typ karoserie</label>
        <div class="select-background">
        <select class="form-control">
          <?php foreach($data['form_body'] as $key => $name): ?>
          <option value="<?php print $key; ?>"><?php print $name; ?></option>
          <?php endforeach; ?>
        </select>
        </div>
      </div>
      <?php endif; ?>
      <div class="item item-action">
        <a href="#" class="btn btn-primary btn-lg form-submit">Filtruj vozy</a>
      </div>
      <div class="item item-advanced collapse" id="categoryAdvancedFilters">
        <div class="item-price">
          <input type="number" value="0" id="price-from">
          <input type="number" value="99999" id="price-to">
        </div>
      </div>
    </div>
    <div class="morelink"><a role="button" data-toggle="collapse" href="#categoryAdvancedFilters" aria-expanded="false" aria-controls="categoryAdvancedFilters"><span class="icon-advanced"></span> <span class="text">Zobrazit rozšířené filtry</span></a></div>
  </div>
  <div class="category-list-sort">
    <div class="item item-sort">
      <ul>
        <li><label><input type="radio" name="sortby" value="recommended" checked="checked"><span>Doporučujeme</span></label></li>
        <li><label><input type="radio" name="sortby" value="cheapest"><span>Od nejlevnějších</span></label></li>
        <li><label><input type="radio" name="sortby" value="expensive"><span>Od nejdražších</span></label></li>
      </li>
    </div>
  </div>
</div>
<?php print $data['product_list']; ?>
