<div class="container">
  <h2><?php print t('We offer cars of these brands'); ?></h2>
  <div class="item-list">
    <?php foreach ($brand as $b): ?>
      <div class="item">
        <a href="<?php print $b['url']; ?>">
          <div class="image">
            <?php print $b['image']; ?>
            <div class="image-hover"><span><?php print t('Offer'); ?></span></div>
          </div>
        </a>
      </div>
    <?php endforeach ?>
  </div>
  <div class="morelink">
    <a href="<?php print $data['morelink']; ?>" class="btn btn-primary btn-lg"><?php print t('Show all cars'); ?></a>
  </div>
</div>
