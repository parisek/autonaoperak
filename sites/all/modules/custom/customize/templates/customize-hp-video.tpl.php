<h2><span>Zdokonalujte se ve stolním tenise</span></h2>
<div class="row item-list">
<?php foreach ($video as $item): ?>
  <div class="col-sm-4 item">
    <?php print $item['node']; ?>
  </div>
<?php endforeach; ?>
</div>
<div class="morelink">
  <a href="<?php print $data['morelink']; ?>" class="btn btn-primary btn-lg">Další videa <span class="glyphicon glyphicon-chevron-right" aria-hidden="true"></span></a>
</div>
