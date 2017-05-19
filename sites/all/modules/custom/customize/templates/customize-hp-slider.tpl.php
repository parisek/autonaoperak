<div class="owl-carousel owl-theme" id="main-slider">
  <?php foreach ($slides as $slide): ?>
    <div class="item" style="background-image:url('<?php print $slide['image']; ?>')">
      <div class="item-inner">
      <?php if($slide['url']): ?>
        <a href="<?php print $slide['url']; ?>" class="carousel-link">
          <div class="text">
            <?php print $slide['body']; ?>
          </div>
        </a>
      <?php else: ?>
        <div class="text">
          <?php print $slide['body']; ?>
        </div>
      <?php endif; ?>
      </div>
    </div>
  <?php endforeach; ?>
</div>
