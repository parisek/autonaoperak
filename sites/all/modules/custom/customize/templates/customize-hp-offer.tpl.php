<div class="container">
  <h2>Přes 50 vozů ihned k dispozici</h2>
  <div class="item-list">
    <?php foreach ($cars as $car): ?>
      <div class="item">
        <a href="<?php print $car['url']; ?>">
          <div class="image"><?php print $car['image']; ?></div>
          <div class="title"><?php print $car['title']; ?></div>
        </a>
      </div>
    <?php endforeach ?>
  </div>
  <div class="morelink">
    <a href="<?php print $data['morelink']; ?>" class="btn btn-primary">Zobrazit všechny vozy skladem</a>
  </div>
</div>
