<div class="container">
  <h2><?php print t('!count vehicles available immediately', ['!count' => '<span class="count" data-count="' . $data['count'] . '" id="offer-count">0</span>']); ?></h2>
  <div class="owl-carousel owl-theme" id="offer-slider">
    <?php foreach ($cars as $car): ?>
      <div class="item">
        <?php print $car['node']; ?>
      </div>
    <?php endforeach ?>
  </div>
  <div class="morelink">
    <a href="<?php print $data['morelink']; ?>" class="btn btn-primary btn-lg"><?php print t('<span class="visible-sm-inline visible-md-inline visible-lg-inline">View </span>all cars in stock'); ?></a>
  </div>
  <div class="block-highlight">
    <?php print $data['highlight']; ?>
  </div>
</div>
