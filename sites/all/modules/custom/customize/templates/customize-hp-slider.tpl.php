<div class="owl-carousel owl-theme" id="main-slider">
  <?php foreach ($slides as $slide): ?>
    <div class="item" style="background-image:url('<?php print $slide['image']; ?>')">
      <div class="item-inner">
        <div class="text">
          <div class="inner">
            <?php print $slide['body']; ?>
          </div>
        </div>
        <div class="highlight">
          <div class="inner">
            <ul>
              <li><span class="icon-car"></span><span class="text">Máme desítky vozů ihned k dispozici</span></li>
              <li><span class="icon-wheel"></span><span class="text">Kalkulaci vám připravíme rychle</span></li>
              <li><span class="icon-wallet"></span><span class="text">Kalkulace je bez skrytých nákladů</span></li>
              <li><span class="icon-calc"></span><span class="text">Kalkulaci vám upravíme na míru dle vašich požadavků</span></li>
            </ul>
          </div>
        </div>
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
