<div class="product-category-list">
<?php foreach ($data['submenu'] as $item): ?>
  <div class="col">
  <div class="item" style="background-image:url('<?php print $item['image']; ?>')">
    <div class="item-inner">
      <a href="<?php print $item['url']; ?>">
        <div class="heading"><?php print $item['title']; ?></div>
      </a>
    </div>
  </div>
  </div>
<?php endforeach; ?>
</div>
