<h2>Vzorová cena operativního leasingu</h2>
<p>Konečnou cenu vám rádi spočítáme na základě vašich požadavků a úprav.</p>
<?php if(count($data['pricelist'])): ?>
  <div class="pricelist hidden-xs hidden-sm">
    <?php foreach($data['pricelist'] as $item): ?>
      <div class="pricelist-item">
        <h3>Roční nájezd: <?php print $item['name']; ?></h3>
        <table class="table">
          <tbody>
          <tr class="year">
            <td class="name">Celková doba operativního leasingu</td>
            <?php foreach($item['year'] as $year): ?>
              <td class="value"><?php print $year['value']; ?></td>
            <?php endforeach; ?>
          </tr>
          <tr class="price">
            <td class="name">Měsíční splátka bez akontace</td>
            <?php foreach($item['price'] as $price): ?>
              <td class="value"><?php print $price['value']; ?></td>
            <?php endforeach; ?>
          </tr>
          <?php foreach($item['deposit'] as $deposit): ?>
            <tr class="deposit">
              <td class="name">Měsíční splátka s akontací <?php print $deposit['name']; ?></td>
              <?php foreach($deposit['items'] as $dep): ?>
                <td class="value"><?php print $dep['value']; ?></td>
              <?php endforeach; ?>
            </tr>
          <?php endforeach; ?>
          </tbody>
        </table>
        <p><small>Ceny jsou uvedeny bez DPH.</small></p>
      </div>
    <?php endforeach; ?>
  </div>
  <div class="pricelist-mobile visible-xs visible-sm">
    <?php foreach($data['pricelist_mobile'] as $item): ?>
      <div class="pricelist-item">
        <div class="item item-year">
          <div class="item-label">Celková doba operativního leasingu:</div>
          <div class="item-value"><strong><?php print $item['year']; ?></strong></div>
        </div>
        <div class="item item-km">
          <div class="item-label">Roční nájezd:</div>
          <div class="item-value"><?php print $item['km']; ?></div>
        </div>
        <div class="item item-price">
          <div class="item-label">Měsíční splátka bez akontace:</div>
          <div class="item-value"><?php print $item['price']; ?></div>
        </div>
        <?php if(!empty($item['deposit'])): ?>
          <div class="item item-deposit">
            <div class="item-label">Měsíční splátka s akontací <?php print $item['deposit']; ?>:</div>
            <div class="item-value"><?php print $item['price2'] ?></div>
          </div>
        <?php endif; ?>
      </div>
    <?php endforeach; ?>
    <p><small>Ceny jsou uvedeny bez DPH.</small></p>
  </div>
<?php endif; ?>
<div class="pricelist-description">
  <div class="row">
    <div class="col-sm-6 col-xs-12 item-left">
      <h3>Splátka obsahuje:</h3>
      <?php print $data['service_included']; ?>
    </div>
    <div class="col-sm-6 col-xs-12 item-right">
      <h3>Splátka neobsahuje:</h3>
      <?php print $data['service_excluded']; ?>
    </div>
  </div>
  <p><strong>Při výběru vozu si můžete vybrat služby navíc, které chcete využívat.</strong></p>
</div>
