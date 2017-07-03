<h2>Vzorová cena operativního leasingu</h2>
<p>Konečnou cenu vám rádi spočítáme na základě vašich požadavků a úprav.</p>
<div class="pricelist">
  <?php foreach($data['pricelist'] as $item): ?>
    <div class="pricelist-item">
      <h3>Roční nájezd: <?php print $item['name']; ?></h3>
      <div class="table-responsive">
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
      </div>
      <p><small>Ceny jsou uvedeny bez DPH.</small></p>
    </div>
  <?php endforeach; ?>
</div>
<div class="pricelist-description">
  <div class="row">
    <div class="col-sm-6 col-xs-12 item-left">
      <h3>Splátka obsahuje:</h3>
      <ul>
        <li>leasingovou splátku</li>
        <li>zákonné pojištění</li>
        <li>pojištění čelního skla</li>
        <li>havarijní pojištění se spoluúčastí 10%</li>
        <li>pojištění finanční ztráty GAP</li>
        <li>silniční daň</li>
        <li>koncesionářský poplatek za rádio</li>
        <li>poplatek za registraci vozidla</li>
      </ul>
    </div>
    <div class="col-sm-6 col-xs-12 item-right">
      <h3>Splátka neobsahuje:</h3>
      <ul>
        <li>Náklady na servis na dobu pronájmu</li>
        <li>Výměnu letních a zimních pneu</li>
        <li>Monitoring firemního vozidla</li>
        <li>Tankovací kartu</li>
        <li>Nadstandardní asistenci</li>
      </ul>
    </div>
  </div>
  <p><strong>Při výběru vozu si můžete vybrat služby navíc, které chcete využívat.</strong></p>
</div>
