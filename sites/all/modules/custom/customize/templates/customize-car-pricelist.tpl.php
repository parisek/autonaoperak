<h2><?php print t('Sample price of operating leases'); ?></h2>
<p><?php print t('The final price will be calculated based on your requirements and adjustments.'); ?></p>
<?php if(count($data['pricelist'])): ?>
  <?php if(count($data['pricelist']) > 1): ?>
    <form class="pricelist-select">
      <div class="form-group">
        <label for="raid"><?php print t('Annual raid'); ?></label>
        <div class="select-background">
        <select class="form-control" id="raid">
          <?php $first = TRUE; ?>
          <?php foreach($data['pricelist'] as $key => $item): ?>
            <option value="<?php print $key; ?>" <?php print ($first) ? 'selected="selected"' : '' ?>><?php print $item['name']; ?></option>
            <?php $first = FALSE; ?>
          <?php endforeach; ?>
        </select>
        </div>
      </div>
    </form>
  <?php endif; ?>
  <div class="pricelist hidden-xs hidden-sm">
    <?php $first = TRUE; ?>
    <?php foreach($data['pricelist'] as $key => $item): ?>
      <?php if(count($data['pricelist']) == 1): ?>
        <h3><?php print t('Annual raid'); ?>: <?php print $item['name']; ?></h3>
      <?php endif; ?>
      <div class="pricelist-item pricelist-item-<?php print $key; ?> <?php print ($first) ? 'show' : 'hide' ?>">
        <?php if($data['pricelist_type'] == 'company'): ?>
        <div class="alert alert-danger"><?php print t('This pricelist is only for companies'); ?></div>
        <?php endif; ?>
        <table class="table">
          <tbody>
          <tr class="year">
            <td class="name"><?php print t('Total operating lease period'); ?></td>
            <?php foreach($item['year'] as $year): ?>
              <td class="value"><?php print $year['value']; ?></td>
            <?php endforeach; ?>
          </tr>
          <tr class="price">
            <?php if($data['car_type'] == 'used'): ?>
              <td class="name"><?php print t('Monthly installment without service'); ?></td>
            <?php else: ?>
              <td class="name"><?php print t('Monthly installment without down payment'); ?></td>
            <?php endif; ?>
            <?php foreach($item['price'] as $price): ?>
              <td class="value"><span class="js-car-price" data-price="<?php print $price['value']['price']; ?>" data-price-vat="<?php print $price['value']['price_vat']; ?>" data-symbol="<?php print $price['value']['currency_symbol']; ?>"><?php print number_format($price['value']['price'], 0, ',', '&nbsp;') . '&nbsp;' . $price['value']['currency_symbol']; ?></span></td>
            <?php endforeach; ?>
          </tr>
          <?php foreach($item['deposit'] as $deposit): ?>
            <tr class="deposit">
              <?php if($data['car_type'] == 'used'): ?>
                <td class="name"><?php print t('Monthly installment with service'); ?></td>
              <?php else: ?>
                <td class="name"><?php print t('Monthly installment with down payment'); ?> <span class="js-car-price" data-price="<?php print $deposit['name']['price']; ?>" data-price-vat="<?php print $deposit['name']['price_vat']; ?>" data-symbol="<?php print $deposit['name']['currency_symbol']; ?>"><?php print number_format($deposit['name']['price'], 0, ',', '&nbsp;') . '&nbsp;' . $deposit['name']['currency_symbol']; ?></span></td>
              <?php endif; ?>
              <?php foreach($deposit['items'] as $dep): ?>
                <td class="value"><span class="js-car-price" data-price="<?php print $dep['value']['price']; ?>" data-price-vat="<?php print $dep['value']['price_vat']; ?>" data-symbol="<?php print $dep['value']['currency_symbol']; ?>"><?php print number_format($dep['value']['price'], 0, ',', '&nbsp;') . '&nbsp;' . $dep['value']['currency_symbol']; ?></span></td>
              <?php endforeach; ?>
            </tr>
          <?php endforeach; ?>
          </tbody>
        </table>
        <p class="js-car-note-vat hide"><small><?php print t('Prices are with @vat % VAT.', ['@vat' => $data['pricelist_vat']]); ?></small></p>
        <p class="js-car-note-without-vat"><small><?php print t('Prices are without @vat % VAT.', ['@vat' => $data['pricelist_vat']]); ?></small></p>
      </div>
      <?php $first = FALSE; ?>
    <?php endforeach; ?>
  </div>
  <div class="pricelist-mobile visible-xs visible-sm">
    <?php $first = TRUE; ?>
    <?php foreach($data['pricelist_mobile'] as $key => $group): ?>
      <?php if(count($data['pricelist_mobile']) == 1): ?>
        <h3><?php print t('Annual raid'); ?>: <?php print $group[0]['km_label']; ?></h3>
      <?php endif; ?>
      <?php foreach($group as $item): ?>
      <div class="pricelist-item pricelist-item-<?php print $item['km']; ?> <?php print ($first) ? 'show' : 'hide' ?>">
        <div class="item item-year">
          <div class="item-label"><?php print t('Total operating lease period'); ?>:</div>
          <div class="item-value"><strong><?php print $item['year']; ?></strong></div>
        </div>
        <div class="item item-price">
          <?php if($data['car_type'] == 'used'): ?>
            <div class="item-label"><?php print t('Monthly installment without service'); ?>:</div>
          <?php else: ?>
            <div class="item-label"><?php print t('Monthly installment without down payment'); ?>:</div>
          <?php endif; ?>
          <div class="item-value"><span class="js-car-price" data-price="<?php print $item['price']; ?>" data-price-vat="<?php print $item['price_vat']; ?>" data-symbol="<?php print $item['currency_symbol']; ?>"><?php print number_format($item['price'], 0, ',', '&nbsp;') . '&nbsp;' . $item['currency_symbol']; ?></span></div>
        </div>
        <?php if(!empty($item['deposit_price'])): ?>
          <div class="item item-deposit">
            <?php if($data['car_type'] == 'used'): ?>
              <div class="item-label"><?php print t('Monthly installment with service'); ?>:</div>
            <?php else: ?>
              <div class="item-label"><?php print t('Monthly installment with down payment'); ?> <span class="js-car-price" data-price="<?php print $item['deposit_price']; ?>" data-price-vat="<?php print $item['deposit_price_vat']; ?>" data-symbol="<?php print $item['currency_symbol']; ?>"><?php print number_format($item['deposit_price'], 0, ',', '&nbsp;') . '&nbsp;' . $item['currency_symbol']; ?></span>:</div>
            <?php endif; ?>
            <div class="item-value"><span class="js-car-price" data-price="<?php print $item['price2']; ?>" data-price-vat="<?php print $item['price2_vat']; ?>" data-symbol="<?php print $item['currency_symbol']; ?>"><?php print number_format($item['price2'], 0, ',', '&nbsp;') . '&nbsp;' . $item['currency_symbol']; ?></span></div>
          </div>
        <?php endif; ?>
      </div>
      <?php endforeach; ?>
      <?php $first = FALSE; ?>
    <?php endforeach; ?>
    <p class="js-car-note-vat hide"><small><?php print t('Prices are with @vat % VAT.', ['@vat' => $data['pricelist_vat']]); ?></small></p>
    <p class="js-car-note-without-vat"><small><?php print t('Prices are without @vat % VAT.', ['@vat' => $data['pricelist_vat']]); ?></small></p>
  </div>
<?php endif; ?>
<div class="pricelist-description">
  <div class="row">
    <div class="col-sm-6 col-xs-12 item-left">
      <h3><?php print t('The installment includes'); ?>:</h3>
      <?php print $data['service_included']; ?>
    </div>
    <div class="col-sm-6 col-xs-12 item-right">
      <h3><?php print t('The installment excludes'); ?>:</h3>
      <?php print $data['service_excluded']; ?>
    </div>
  </div>
  <p><strong><?php print t('When choosing a car, you can select additional services that you want to use.'); ?></strong></p>
</div>
