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
<?php
global $language;
?>
<?php if($language->language == 'cs'): ?>
<div class="used-cars">
  <div class="item-list">
    <div class="image">
      <img src="/sites/all/themes/autonaoperak/images/rocni-vozy.jpg" class="img-responsive" alt="">
    </div>
    <div class="text">
      <div class="text-inner">
      <h2>Roční vozy</h2>
      <ul>
        <li>Jsou <strong>ihned k dispozici</strong> = Zítra můžete jezdit</li>
        <li>Dají se pronajmout na dobu <strong>od 1 roku</strong></li>
        <li>Tato akce trvá <strong>jen do konce roku 2017</strong></li>
      </ul>
      <div class="morelink"><a href="<?php print customize_get_translate_link('node/443'); ?>" class="btn btn-primary">Zobrazit nabídku</a></div>
      </div>
    </div>
  </div>
</div>
<?php endif; ?>
