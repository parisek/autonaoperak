<div class="container">
  <h2>Nabízíme osobní vozy těchto značek</h2>
  <div class="item-list">
    <?php foreach ($brand as $b): ?>
      <div class="item">
        <a href="<?php print $b['url']; ?>">
          <div class="title"><?php print $b['title']; ?></div>
          <div class="image"><?php print $b['image']; ?></div>
        </a>
      </div>
    <?php endforeach ?>
  </div>
  <div class="morelink">
    <a href="<?php print $data['morelink']; ?>" class="btn btn-primary">Zobrazit všechny osobní vozy</a>
  </div>
</div>
