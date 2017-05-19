<?php if(count($data['submenu'])): ?>
  <div class="product-filter">
    <ul>
    <?php foreach ($data['submenu'] as $item): ?>
      <li><?php print l($item['title'], $item['url']); ?></li>
    <?php endforeach; ?>
    </ul>
  </div>
<?php endif; ?>
<?php print $data['products']; ?>
