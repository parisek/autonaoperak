<ul>
  <?php foreach ($items as $item): ?>
    <li>
      <a href="<?php print $item['url']; ?>" class="item<?php print ($item['active']) ? ' item-active': ''; ?>">
        <div class="image">
          <?php print $item['image']; ?>
        </div>
        <div class="title">
          <?php print $item['name']; ?>
        </div>
      </a>
    </li>
  <?php endforeach ?>
</ul>
