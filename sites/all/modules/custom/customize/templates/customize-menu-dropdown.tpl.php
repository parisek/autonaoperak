<ul class="menu menu-level-1">
<?php foreach ($data['menu'] as $item): ?>
  <li class="<?php print implode($item['class'], ' '); ?>">
    <a href="<?php print $item['url']; ?>">
      <?php print $item['title']; ?>
    </a>
    <?php if(count($item['submenu'])): ?>
      <div class="submenu-wrapper">
        <ul class="menu menu-level-2">
        <?php foreach ($item['submenu'] as $item2): ?>
          <li class="<?php print implode($item2['class'], ' '); ?>">
            <a href="<?php print $item2['url']; ?>">
              <span><?php print $item2['title']; ?></span>
            </a>
            <?php if(count($item2['below'])): ?>
              <ul class="menu menu-level-3">
              <?php foreach ($item2['below'] as $item3): ?>
                <li class="<?php print implode($item3['class'], ' '); ?>">
                  <a href="<?php print $item3['url']; ?>">
                    <?php print $item3['title']; ?>
                  </a>
                </li>
              <?php endforeach; ?>
              </ul>
            <?php endif; ?>
          </li>
        <?php endforeach; ?>
        </ul>
      </div>
    <?php endif; ?>
  </li>
<?php endforeach; ?>
</ul>
