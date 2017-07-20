<div class="container">
  <h2><span class="count" data-count="<?php print $data['count']; ?>" id="offer-count">0</span> vozů ihned k dispozici</h2>
  <div class="owl-carousel owl-theme" id="offer-slider">
    <?php foreach ($cars as $car): ?>
      <div class="item">
        <?php print $car['node']; ?>
      </div>
    <?php endforeach ?>
  </div>
  <div class="morelink">
    <a href="<?php print $data['morelink']; ?>" class="btn btn-primary btn-lg"><span class="visible-sm-inline visible-md-inline visible-lg-inline">Zobrazit </span>všechny vozy skladem</a>
  </div>
  <div class="block-highlight">
    <?php print $data['highlight']; ?>
  </div>
</div>
