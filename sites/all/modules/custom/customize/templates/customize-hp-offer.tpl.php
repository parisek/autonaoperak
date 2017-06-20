<div class="container">
  <h2>Přes 50 vozů ihned k dispozici</h2>
  <div class="owl-carousel owl-theme" id="offer-slider">
    <?php foreach ($cars as $car): ?>
      <div class="item">
        <?php print $car['node']; ?>
      </div>
    <?php endforeach ?>
  </div>
  <div class="morelink">
    <a href="<?php print $data['morelink']; ?>" class="btn btn-primary">Zobrazit všechny vozy skladem</a>
  </div>
</div>
