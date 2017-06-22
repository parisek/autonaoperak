<ul class="menu menu-1">
  <?php foreach ($brand as $b): ?>
    <li class="first-level <?php print $b['status']; ?>">
      <?php if(count($b['model'])): ?>
        <?php print l($b['title'] . '<span class="submenu-toggle icon-down"></span>', $b['url'], ['html' => TRUE, 'attributes' => ['class' => $b['class']]]); ?>
        <ul class="menu menu-2">
        <?php foreach ($b['model'] as $m): ?>
          <li class="second-level"><?php print l($m['title'], $m['url'], ['attributes' => ['class' => $m['class']]]); ?></li>
        <?php endforeach ?>
        </ul>
      <?php else: ?>
        <?php print l($b['title'], $b['url'], ['attributes' => ['class' => $b['class']]]); ?>
      <?php endif; ?>
    </li>
  <?php endforeach ?>
</ul>
