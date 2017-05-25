<ul class="menu">
  <?php foreach ($brand as $b): ?>
    <li>
      <?php print l($b['title'], $b['url']); ?>
      <?php if(count($b['model'])): ?>
      <ul>
      <?php foreach ($b['model'] as $m): ?>
        <li><?php print l($m['title'], $m['url']); ?></li>
      <?php endforeach ?>
      </ul>
      <?php endif; ?>
    </li>
  <?php endforeach ?>
</ul>
