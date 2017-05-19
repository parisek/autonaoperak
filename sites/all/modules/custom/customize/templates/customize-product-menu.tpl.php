<div class="content">
<?php foreach ($data['menu'] as $item): ?>
  <ul>
    <li class="<?php print implode($item['class'], ' '); ?>">
      <a href="<?php print $item['url']; ?>"><?php print $item['title']; ?></a>
      <?php if(count($item['below'])): ?>
        <ul>
        <?php foreach ($item['below'] as $item2): ?>
          <li class="<?php print implode($item2['class'], ' '); ?>">
            <a href="<?php print $item2['url']; ?>"><?php print $item2['title']; ?></a>
          </li>
        <?php endforeach; ?>
        </ul>
      <?php endif; ?>
    </li>
  </ul>
<?php endforeach; ?>
</div>
