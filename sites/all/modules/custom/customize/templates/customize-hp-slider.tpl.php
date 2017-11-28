<div class="owl-carousel owl-theme" id="main-slider">
  <?php foreach ($slides as $slide): ?>
    <div class="item" style="background-image:url('<?php print $slide['image']; ?>')">
      <div class="container">
        <?php if(!empty($slide['link'])): ?>
        <a href="<?php print $slide['link']; ?>" class="link">
          <div class="text">
            <div class="inner">
              <?php print $slide['body']; ?>
            </div>
          </div>
        </a>
        <?php else: ?>
          <div class="text">
            <div class="inner">
              <?php print $slide['body']; ?>
            </div>
          </div>
        <?php endif; ?>
      </div>
    </div>
  <?php endforeach; ?>
</div>
<div class="slider-nav">
  <div class="gradient-left"></div>
  <div class="gradient-right"></div>
  <div class="container">
    <ul id='carousel-custom-dots' class='owl-dots'>
      <?php foreach ($slides as $slide): ?>
      <li class='owl-dot'><?php print $slide['anotation']; ?></li>
      <?php endforeach; ?>
    </ul>
  </div>
</div>
